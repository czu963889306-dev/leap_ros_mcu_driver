# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target geometry_msgs::geometry_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${geometry_msgs_TARGETS}.
if(geometry_msgs_TARGETS AND NOT TARGET geometry_msgs::geometry_msgs)
  add_library(geometry_msgs::geometry_msgs INTERFACE IMPORTED)
  set_target_properties(geometry_msgs::geometry_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${geometry_msgs_TARGETS}")
endif()
