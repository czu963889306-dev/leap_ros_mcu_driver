cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(leap_ros)

if(TARGET merge-bin)
    add_custom_target(merged_bin ALL DEPENDS merge-bin)
endif()
