# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target leap_interfaces::leap_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${leap_interfaces_TARGETS}.
if(leap_interfaces_TARGETS AND NOT TARGET leap_interfaces::leap_interfaces)
  add_library(leap_interfaces::leap_interfaces INTERFACE IMPORTED)
  set_target_properties(leap_interfaces::leap_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${leap_interfaces_TARGETS}")
endif()
