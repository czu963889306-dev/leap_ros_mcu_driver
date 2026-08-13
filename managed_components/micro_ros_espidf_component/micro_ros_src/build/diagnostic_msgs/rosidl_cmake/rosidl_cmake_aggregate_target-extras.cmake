# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target diagnostic_msgs::diagnostic_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${diagnostic_msgs_TARGETS}.
if(diagnostic_msgs_TARGETS AND NOT TARGET diagnostic_msgs::diagnostic_msgs)
  add_library(diagnostic_msgs::diagnostic_msgs INTERFACE IMPORTED)
  set_target_properties(diagnostic_msgs::diagnostic_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${diagnostic_msgs_TARGETS}")
endif()
