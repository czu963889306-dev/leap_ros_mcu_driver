# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target visualization_msgs::visualization_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${visualization_msgs_TARGETS}.
if(visualization_msgs_TARGETS AND NOT TARGET visualization_msgs::visualization_msgs)
  add_library(visualization_msgs::visualization_msgs INTERFACE IMPORTED)
  set_target_properties(visualization_msgs::visualization_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${visualization_msgs_TARGETS}")
endif()
