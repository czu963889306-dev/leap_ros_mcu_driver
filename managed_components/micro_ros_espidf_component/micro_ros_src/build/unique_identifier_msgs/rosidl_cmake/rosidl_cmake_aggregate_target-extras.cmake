# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target unique_identifier_msgs::unique_identifier_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${unique_identifier_msgs_TARGETS}.
if(unique_identifier_msgs_TARGETS AND NOT TARGET unique_identifier_msgs::unique_identifier_msgs)
  add_library(unique_identifier_msgs::unique_identifier_msgs INTERFACE IMPORTED)
  set_target_properties(unique_identifier_msgs::unique_identifier_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${unique_identifier_msgs_TARGETS}")
endif()
