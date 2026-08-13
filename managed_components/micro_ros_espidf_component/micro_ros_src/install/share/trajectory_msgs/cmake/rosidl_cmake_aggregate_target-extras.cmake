# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target trajectory_msgs::trajectory_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${trajectory_msgs_TARGETS}.
if(trajectory_msgs_TARGETS AND NOT TARGET trajectory_msgs::trajectory_msgs)
  add_library(trajectory_msgs::trajectory_msgs INTERFACE IMPORTED)
  set_target_properties(trajectory_msgs::trajectory_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${trajectory_msgs_TARGETS}")
endif()
