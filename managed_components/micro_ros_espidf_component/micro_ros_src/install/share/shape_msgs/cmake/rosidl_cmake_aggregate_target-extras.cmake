# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target shape_msgs::shape_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${shape_msgs_TARGETS}.
if(shape_msgs_TARGETS AND NOT TARGET shape_msgs::shape_msgs)
  add_library(shape_msgs::shape_msgs INTERFACE IMPORTED)
  set_target_properties(shape_msgs::shape_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${shape_msgs_TARGETS}")
endif()
