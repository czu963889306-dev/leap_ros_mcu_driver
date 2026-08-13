# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target statistics_msgs::statistics_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${statistics_msgs_TARGETS}.
if(statistics_msgs_TARGETS AND NOT TARGET statistics_msgs::statistics_msgs)
  add_library(statistics_msgs::statistics_msgs INTERFACE IMPORTED)
  set_target_properties(statistics_msgs::statistics_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${statistics_msgs_TARGETS}")
endif()
