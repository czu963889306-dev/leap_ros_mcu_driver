# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target std_msgs::std_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${std_msgs_TARGETS}.
if(std_msgs_TARGETS AND NOT TARGET std_msgs::std_msgs)
  add_library(std_msgs::std_msgs INTERFACE IMPORTED)
  set_target_properties(std_msgs::std_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${std_msgs_TARGETS}")
endif()
