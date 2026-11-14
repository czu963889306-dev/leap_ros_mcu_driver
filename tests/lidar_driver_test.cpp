#include "ldstl26_lidar.h"
#include "camsense_lidar.h"
#include "lidar_detection.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <vector>

static std::deque<uint8_t> received;
static int configured_baud = 0;

int uart_driver_install(uart_port_t port, int size, int, int, void*, int) {
    assert(port == 1 && size >= 512);
    return 0;
}
int uart_param_config(uart_port_t, const uart_config_t* config) {
    configured_baud = config->baud_rate;
    return 0;
}
int uart_set_pin(uart_port_t, int tx, int rx, int, int) {
    assert(tx == -1 && rx == 41);
    return 0;
}
int uart_get_buffered_data_len(uart_port_t, size_t* size) {
    *size = received.size();
    return 0;
}
int uart_read_bytes(uart_port_t, void* data, uint32_t size, int) {
    auto* bytes = static_cast<uint8_t*>(data);
    const size_t count = std::min<size_t>(size, received.size());
    for (size_t i = 0; i < count; ++i) {
        bytes[i] = received.front();
        received.pop_front();
    }
    return static_cast<int>(count);
}

static void put_u16(std::vector<uint8_t>& bytes, size_t index, uint16_t value) {
    bytes[index] = value & 0xFF;
    bytes[index + 1] = value >> 8;
}

static void update_stl_crc(std::vector<uint8_t>& bytes) {
    // Polynomial division by x^8 + x^6 + x^3 + x^2 + 1.
    uint16_t remainder = 0;
    for (size_t i = 0; i < 46; ++i) {
        remainder ^= static_cast<uint16_t>(bytes[i]) << 8;
        for (int bit = 15; bit >= 8; --bit) {
            if (remainder & (1U << bit)) {
                remainder ^= 0x14D << (bit - 8);
            }
        }
        remainder <<= 8;
    }
    bytes[46] = remainder >> 8;
}

static std::vector<uint8_t> stl_packet(uint16_t start, uint16_t end, uint16_t distance = 50) {
    std::vector<uint8_t> bytes(47);
    bytes[0] = 0x54;
    bytes[1] = 0x2C;
    put_u16(bytes, 4, start);
    put_u16(bytes, 42, end);
    for (int i = 0; i < 12; ++i) {
        put_u16(bytes, 6 + i * 3, distance);
        bytes[8 + i * 3] = 100;
    }
    update_stl_crc(bytes);
    return bytes;
}

static std::vector<uint8_t> camsense_packet(int start, int end, uint16_t distance = 1000) {
    // 12 distance records, matching the existing Camsense wire format.
    std::vector<uint8_t> bytes(4 + 8 + 12 * 2);
    bytes[0] = 0x55;
    bytes[1] = 0xAA;
    bytes[2] = 2;
    bytes[3] = 12;
    put_u16(bytes, 6, 0xA000 + start * 64);
    for (int i = 0; i < 12; ++i) {
        put_u16(bytes, 8 + i * 2, distance);
    }
    put_u16(bytes, 32, 0xA000 + end * 64);
    return bytes;
}

struct Scan {
    LidarPoint points[MAX_LIDAR_POINTS_PER_SCAN];
    uint64_t guard = 0x123456789ABCDEF0ULL;
    uint16_t count = 0;
};

template <class Driver>
static bool feed(Driver& driver, const std::vector<uint8_t>& bytes, Scan& scan) {
    bool completed = false;
    // Deliberately split headers, payloads and CRC across reads.
    for (size_t offset = 0; offset < bytes.size(); offset += 7) {
        const size_t end = std::min(offset + 7, bytes.size());
        received.insert(received.end(), bytes.begin() + offset, bytes.begin() + end);
        completed = driver.Poll(scan.points, &scan.count) || completed;
        assert(scan.guard == 0x123456789ABCDEF0ULL);
    }
    return completed;
}

static void test_stl_full_turn() {
    Ldstl26Lidar driver(1, -1, 41);
    driver.Init();
    assert(configured_baud == 230400);
    Scan scan;
    // Two dense turns exercise the corrected wrap and all angular bins.
    bool complete = false;
    for (int turn = 0; turn < 2; ++turn) {
        for (int i = 0; i < 120; ++i) {
            auto packet = stl_packet(i * 300, i * 300 + 275);
            if (i == 60) {
                put_u16(packet, 6, 25);
                update_stl_crc(packet);
            }
            complete = feed(driver, packet, scan) || complete;
        }
    }
    assert(complete && scan.count == 360);
    for (int angle = 0; angle < 360; ++angle) {
        assert(scan.points[angle].angle == angle);
        assert(scan.points[angle].distance == (angle == 180 ? 25 : 50));
    }
    assert(LidarMirroredAngle(19.0f) == 341);
    assert(LidarMirroredAngle(359.0f) == 1);
    assert(driver.ValidPacketCount() == 240);
    driver.Reset();
    assert(driver.ValidPacketCount() == 0);
    complete = false;
    for (int turn = 0; turn < 2; ++turn) {
        for (int i = 0; i < 30; ++i) {
            complete = feed(driver, stl_packet(i * 1200, i * 1200 + 1100, 0), scan) || complete;
        }
    }
    assert(complete && scan.count == 0 && driver.ValidPacketCount() == 60);
}

static void test_stl_bad_data() {
    Ldstl26Lidar driver(1, -1, 41);
    Scan scan;
    auto bad_crc = stl_packet(0, 1100);
    bad_crc.back() ^= 1;
    feed(driver, bad_crc, scan);
    feed(driver, stl_packet(36001, 1100), scan);
    feed(driver, camsense_packet(0, 11), scan);
    assert(driver.ValidPacketCount() == 0);
    // An overlapping sync byte must not lose the following valid header.
    feed(driver, {0x54}, scan);
    feed(driver, stl_packet(0, 1100), scan);
    assert(driver.ValidPacketCount() == 1);
    driver.Reset();
    assert(driver.ValidPacketCount() == 0);
    feed(driver, stl_packet(0, 1100), scan);
    assert(driver.ValidPacketCount() == 1);
    feed(driver, stl_packet(36000, 1100), scan);
    assert(driver.ValidPacketCount() == 2);
}

static void test_camsense() {
    CamsenseLidar driver(1, -1, 41);
    driver.Init();
    assert(configured_baud == 115200);
    Scan scan;
    feed(driver, stl_packet(0, 1100), scan);
    auto bad = camsense_packet(0, 11);
    bad[7] = 0;
    feed(driver, bad, scan);
    feed(driver, {0x55, 0xAA, 2, 0, 0x55, 0xAA, 3, 12}, scan);
    assert(driver.ValidPacketCount() == 0);
    bool complete = false;
    // Two turns provide one full revolution after the legacy 18.5-degree correction.
    for (int turn = 0; turn < 2; ++turn) {
        for (int i = 0; i < 30; ++i) {
            if (feed(driver, camsense_packet(i * 12, i * 12 + 11), scan)) {
                complete = true;
            }
        }
    }
    assert(complete && scan.count == 360);
    for (int i = 0; i < 360; ++i) {
        assert(scan.points[i].angle == i && scan.points[i].distance == 1000);
    }
    driver.Reset();
    assert(driver.ValidPacketCount() == 0);
    feed(driver, camsense_packet(0, 11), scan);
    assert(driver.ValidPacketCount() == 1);
}

static void test_detection() {
    LidarDetection detection(1500, 2000, 3);
    detection.Begin(0);
    assert(detection.ProbeModel() == LidarModel::kStl26);
    assert(!detection.Update(1499, 0));
    assert(detection.Update(1500, 0));
    assert(detection.ProbeModel() == LidarModel::kCamsense);
    assert(!detection.Update(1510, 1));
    assert(!detection.Update(1520, 2));
    assert(detection.DetectedModel() == LidarModel::kUnknown);
    assert(!detection.Update(1530, 3));
    assert(detection.DetectedModel() == LidarModel::kCamsense);
    assert(!detection.Update(3000, 4));
    assert(!detection.Update(4999, 4));
    assert(detection.Update(5000, 4));
    assert(detection.DetectedModel() == LidarModel::kUnknown);
    assert(detection.ProbeModel() == LidarModel::kStl26);
    assert(!detection.Update(5010, 3));
    assert(detection.DetectedModel() == LidarModel::kStl26);
    assert(!detection.Update(6500, 3));
    assert(detection.Update(7010, 3));
    // Uptime wrap and repeated probing with no connected sensor.
    detection.Begin(UINT32_MAX - 1000);
    assert(!detection.Update(498, 0));
    assert(detection.Update(499, 0));
    assert(detection.ProbeModel() == LidarModel::kCamsense);
    assert(detection.Update(1999, 0));
    assert(detection.ProbeModel() == LidarModel::kStl26);
}

int main() {
    test_stl_full_turn();
    test_stl_bad_data();
    test_camsense();
    test_detection();
    std::puts("PASS: STL26 full 360 degrees, dense/empty scans, near returns, CRC/angle rejection,");
    std::puts("      Camsense parsing, baud probing, model locking, disconnect recovery, uptime wrap");
}
