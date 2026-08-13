# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target lifecycle_msgs::lifecycle_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${lifecycle_msgs_TARGETS}.
if(lifecycle_msgs_TARGETS AND NOT TARGET lifecycle_msgs::lifecycle_msgs)
  add_library(lifecycle_msgs::lifecycle_msgs INTERFACE IMPORTED)
  set_target_properties(lifecycle_msgs::lifecycle_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${lifecycle_msgs_TARGETS}")
endif()
