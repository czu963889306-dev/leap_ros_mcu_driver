cmake_minimum_required(VERSION 3.16)
project(microros_time_sync_tests LANGUAGES CXX)

enable_testing()
add_executable(microros_time_sync_test
    time_sync_pro_test.cpp
    ../main/tasks/network/microros/microros_time_sync.cpp)
target_compile_features(microros_time_sync_test PRIVATE cxx_std_11)
target_compile_options(microros_time_sync_test PRIVATE -Wall -Wextra -Werror -UNDEBUG)
target_include_directories(microros_time_sync_test PRIVATE
    time_sync_pro_stubs
    ../main/config
    ../main/tasks/network/microros)
add_test(NAME microros_time_sync COMMAND microros_time_sync_test)
