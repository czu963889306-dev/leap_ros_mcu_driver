# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target rcl_interfaces::rcl_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${rcl_interfaces_TARGETS}.
if(rcl_interfaces_TARGETS AND NOT TARGET rcl_interfaces::rcl_interfaces)
  add_library(rcl_interfaces::rcl_interfaces INTERFACE IMPORTED)
  set_target_properties(rcl_interfaces::rcl_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${rcl_interfaces_TARGETS}")
endif()
