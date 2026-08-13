# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target builtin_interfaces::builtin_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${builtin_interfaces_TARGETS}.
if(builtin_interfaces_TARGETS AND NOT TARGET builtin_interfaces::builtin_interfaces)
  add_library(builtin_interfaces::builtin_interfaces INTERFACE IMPORTED)
  set_target_properties(builtin_interfaces::builtin_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${builtin_interfaces_TARGETS}")
endif()
