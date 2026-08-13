# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target rosgraph_msgs::rosgraph_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${rosgraph_msgs_TARGETS}.
if(rosgraph_msgs_TARGETS AND NOT TARGET rosgraph_msgs::rosgraph_msgs)
  add_library(rosgraph_msgs::rosgraph_msgs INTERFACE IMPORTED)
  set_target_properties(rosgraph_msgs::rosgraph_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${rosgraph_msgs_TARGETS}")
endif()
