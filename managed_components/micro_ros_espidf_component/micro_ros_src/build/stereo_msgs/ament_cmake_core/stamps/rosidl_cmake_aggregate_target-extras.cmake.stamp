# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target stereo_msgs::stereo_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${stereo_msgs_TARGETS}.
if(stereo_msgs_TARGETS AND NOT TARGET stereo_msgs::stereo_msgs)
  add_library(stereo_msgs::stereo_msgs INTERFACE IMPORTED)
  set_target_properties(stereo_msgs::stereo_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${stereo_msgs_TARGETS}")
endif()
