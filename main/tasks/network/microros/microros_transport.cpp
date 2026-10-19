#include "microros_internal.h"

namespace microros {

extern "C" bool transport_open_udp(uxrCustomTransport *transport) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    ctx->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (ctx->fd < 0) {
        return false;
    }

    sockaddr_in local = {};
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(ctx->local_port);
    bind(ctx->fd, reinterpret_cast<sockaddr *>(&local), sizeof(local));
    return true;
}

extern "C" bool transport_close_udp(uxrCustomTransport *transport) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    if (ctx->fd >= 0) {
        close(ctx->fd);
        ctx->fd = -1;
    }
    return true;
}

extern "C" size_t transport_write_udp(
    uxrCustomTransport *transport,
    const uint8_t *buf,
    size_t len,
    uint8_t *) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    const int sent = sendto(
        ctx->fd,
        buf,
        len,
        0,
        reinterpret_cast<sockaddr *>(&ctx->remote),
        sizeof(ctx->remote));
    return sent > 0 ? static_cast<size_t>(sent) : 0;
}

extern "C" size_t transport_read_udp(
    uxrCustomTransport *transport,
    uint8_t *buf,
    size_t len,
    int timeout,
    uint8_t *) {
    auto *ctx = static_cast<UdpTransportContext *>(transport->args);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(ctx->fd, &readfds);

    timeval tv = {};
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
    const int ret = select(ctx->fd + 1, &readfds, nullptr, nullptr, &tv);
    if (ret <= 0) {
        return 0;
    }

    const int received = recv(ctx->fd, buf, len, 0);
    return received > 0 ? static_cast<size_t>(received) : 0;
}

static bool ensure_uart_driver_initialized(UartTransportContext *ctx) {
    if (ctx == nullptr) {
        return false;
    }

    if (s_uart_transport_initialized && uart_is_driver_installed(ctx->port)) {
        return true;
    }

    const uart_config_t uart_config = {
        .baud_rate = net_cfg::kMicroRosUartBaudRate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = {},
    };

    const bool driver_already_installed = uart_is_driver_installed(ctx->port);
    esp_err_t err = ESP_OK;
    if (!driver_already_installed) {
        err = uart_driver_install(
            ctx->port,
            net_cfg::kMicroRosUartRxBufferSize,
            net_cfg::kMicroRosUartTxBufferSize,
            0,
            nullptr,
            0);
        if (err != ESP_OK) {
            ESP_LOGE(kTag, "failed to install UART%d driver: %s",
                     static_cast<int>(ctx->port), esp_err_to_name(err));
            return false;
        }
    }

    err = uart_param_config(ctx->port, &uart_config);
    if (err != ESP_OK) {
        ESP_LOGE(kTag, "failed to configure UART%d: %s",
                 static_cast<int>(ctx->port), esp_err_to_name(err));
        if (!driver_already_installed) {
            uart_driver_delete(ctx->port);
        }
        return false;
    }

    err = uart_set_pin(
        ctx->port,
        net_cfg::kMicroRosUartTxPin,
        net_cfg::kMicroRosUartRxPin,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE);
    if (err != ESP_OK) {
        ESP_LOGE(kTag, "failed to set UART%d pins: %s",
                 static_cast<int>(ctx->port), esp_err_to_name(err));
        if (!driver_already_installed) {
            uart_driver_delete(ctx->port);
        }
        return false;
    }

    uart_flush_input(ctx->port);
    s_uart_transport_initialized = true;
    return true;
}

static bool transport_open_uart(uxrCustomTransport *transport) {
    if (transport == nullptr) {
        return false;
    }
    return ensure_uart_driver_initialized(
        static_cast<UartTransportContext *>(transport->args));
}

static bool transport_close_uart(uxrCustomTransport *transport) {
    return transport != nullptr && transport->args != nullptr;
}

static size_t transport_write_uart(
    uxrCustomTransport *transport,
    const uint8_t *buf,
    size_t len,
    uint8_t *) {
    if (transport == nullptr || transport->args == nullptr || buf == nullptr || len == 0) {
        return 0;
    }

    auto *ctx = static_cast<UartTransportContext *>(transport->args);
    const int written = uart_write_bytes(
        ctx->port, reinterpret_cast<const char *>(buf), len);
    return written > 0 ? static_cast<size_t>(written) : 0;
}

static size_t transport_read_uart(
    uxrCustomTransport *transport,
    uint8_t *buf,
    size_t len,
    int timeout,
    uint8_t *) {
    if (transport == nullptr || transport->args == nullptr || buf == nullptr || len == 0) {
        return 0;
    }

    auto *ctx = static_cast<UartTransportContext *>(transport->args);
    const int wait_ms = timeout <= 0
        ? 0
        : (timeout > net_cfg::kMicroRosUartReadMaxWaitMs ? net_cfg::kMicroRosUartReadMaxWaitMs : timeout);
    const int received = uart_read_bytes(ctx->port, buf, len, pdMS_TO_TICKS(wait_ms));
    taskYIELD();
    return received > 0 ? static_cast<size_t>(received) : 0;
}

bool setup_udp_transport() {
    memset(&s_udp_ctx, 0, sizeof(s_udp_ctx));
    s_udp_ctx.fd = -1;
    s_udp_ctx.local_port = static_cast<uint16_t>(atoi(net_cfg::kMicroRosLocalPort));
    s_udp_ctx.remote.sin_family = AF_INET;
    s_udp_ctx.remote.sin_port = htons(system_globals().runtime.microros_agent_port);

    if (inet_pton(AF_INET, system_globals().runtime.microros_agent_ip, &s_udp_ctx.remote.sin_addr.s_addr) != 1) {
        ESP_LOGE(kTag, "invalid micro-ROS agent IP: %s", system_globals().runtime.microros_agent_ip);
        return false;
    }

    rmw_uros_set_custom_transport(
        false,
        &s_udp_ctx,
        transport_open_udp,
        transport_close_udp,
        transport_write_udp,
        transport_read_udp);
    return true;
}

bool setup_uart_transport() {
    memset(&s_uart_ctx, 0, sizeof(s_uart_ctx));
    s_uart_ctx.port = net_cfg::kMicroRosUartPort;
    rmw_uros_set_custom_transport(
        true,
        &s_uart_ctx,
        transport_open_uart,
        transport_close_uart,
        transport_write_uart,
        transport_read_uart);
    return true;
}

}  // namespace microros
