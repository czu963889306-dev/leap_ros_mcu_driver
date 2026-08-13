# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target actionlib_msgs::actionlib_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${actionlib_msgs_TARGETS}.
if(actionlib_msgs_TARGETS AND NOT TARGET actionlib_msgs::actionlib_msgs)
  add_library(actionlib_msgs::actionlib_msgs INTERFACE IMPORTED)
  set_target_properties(actionlib_msgs::actionlib_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${actionlib_msgs_TARGETS}")
endif()
