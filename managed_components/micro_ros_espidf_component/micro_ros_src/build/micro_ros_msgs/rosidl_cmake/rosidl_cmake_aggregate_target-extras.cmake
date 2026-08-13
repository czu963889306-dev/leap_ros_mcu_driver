# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target micro_ros_msgs::micro_ros_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${micro_ros_msgs_TARGETS}.
if(micro_ros_msgs_TARGETS AND NOT TARGET micro_ros_msgs::micro_ros_msgs)
  add_library(micro_ros_msgs::micro_ros_msgs INTERFACE IMPORTED)
  set_target_properties(micro_ros_msgs::micro_ros_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${micro_ros_msgs_TARGETS}")
endif()
