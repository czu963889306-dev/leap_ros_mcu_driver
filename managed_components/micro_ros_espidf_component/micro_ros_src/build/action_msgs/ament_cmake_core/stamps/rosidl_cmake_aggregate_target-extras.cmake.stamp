# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target action_msgs::action_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${action_msgs_TARGETS}.
if(action_msgs_TARGETS AND NOT TARGET action_msgs::action_msgs)
  add_library(action_msgs::action_msgs INTERFACE IMPORTED)
  set_target_properties(action_msgs::action_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${action_msgs_TARGETS}")
endif()
