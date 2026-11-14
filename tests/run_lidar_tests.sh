#!/usr/bin/env bash
set -euo pipefail
repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
test_build="$(mktemp -d /tmp/leap_lidar_tests.XXXXXX)"
trap 'rm -rf "$test_build"' EXIT

g++ -std=c++17 -Wall -Wextra -Werror -fsanitize=address,undefined -g \
    -I "$repo_root/tests/lidar_stubs" \
    -I "$repo_root/components/lidar_common/include" \
    -I "$repo_root/components/ldstl26_lidar" \
    -I "$repo_root/components/camsense_lidar" \
    -I "$repo_root/main/tasks/sensors" \
    "$repo_root/tests/lidar_driver_test.cpp" \
    "$repo_root/components/ldstl26_lidar/ldstl26_lidar.cpp" \
    "$repo_root/components/camsense_lidar/camsense_lidar.cpp" \
    -o "$test_build/lidar_driver_test"
"$test_build/lidar_driver_test"
