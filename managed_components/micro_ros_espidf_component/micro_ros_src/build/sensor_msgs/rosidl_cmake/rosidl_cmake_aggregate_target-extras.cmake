# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target sensor_msgs::sensor_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${sensor_msgs_TARGETS}.
if(sensor_msgs_TARGETS AND NOT TARGET sensor_msgs::sensor_msgs)
  add_library(sensor_msgs::sensor_msgs INTERFACE IMPORTED)
  set_target_properties(sensor_msgs::sensor_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${sensor_msgs_TARGETS}")
endif()
