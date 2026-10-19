#include "differential_kinematics.h"

#include <cassert>
#include <cmath>
#include <initializer_list>

static void ExpectNear(float actual, float expected) {
    assert(std::fabs(actual - expected) < 0.0001f);
}

int main() {
    DifferentialKinematics kinematics;
    float wheels[2] = {};
    float vx, vy, wz;

    // Straight motion, reverse motion, and stop produce equal wheel speeds.
    for (float speed : {0.0f, 300.0f, -300.0f}) {
        kinematics.Inverse(speed, 0.0f, 0.0f, wheels);
        ExpectNear(wheels[0], speed);
        ExpectNear(wheels[1], speed);
    }

    // Positive yaw turns left: left wheel reverses, right wheel advances.
    kinematics.Inverse(0.0f, 0.0f, 2.0f, wheels);
    ExpectNear(wheels[0], -131.7f);
    ExpectNear(wheels[1], 131.7f);
    kinematics.Forward(wheels, &vx, &vy, &wz);
    ExpectNear(vx, 0.0f);
    ExpectNear(vy, 0.0f);
    ExpectNear(wz, 2.0f);

    // Differential drive rejects lateral motion; curved paths round-trip.
    for (float speed : {-250.0f, 0.0f, 250.0f}) {
        for (float yaw : {-2.5f, 0.0f, 2.5f}) {
            kinematics.Inverse(speed, 123.0f, yaw, wheels);
            kinematics.Forward(wheels, &vx, &vy, &wz);
            ExpectNear(vx, speed);
            ExpectNear(vy, 0.0f);
            ExpectNear(wz, yaw);
        }
    }

    // Incomplete outputs must not be partially overwritten.
    vx = 42.0f;
    kinematics.Forward(wheels, &vx, nullptr, &wz);
    ExpectNear(vx, 42.0f);
    kinematics.Forward(nullptr, &vx, &vy, &wz);
    ExpectNear(vx, 42.0f);
    kinematics.Inverse(0.0f, 0.0f, 0.0f, nullptr);
}
