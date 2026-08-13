# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target test_msgs::test_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${test_msgs_TARGETS}.
if(test_msgs_TARGETS AND NOT TARGET test_msgs::test_msgs)
  add_library(test_msgs::test_msgs INTERFACE IMPORTED)
  set_target_properties(test_msgs::test_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${test_msgs_TARGETS}")
endif()
