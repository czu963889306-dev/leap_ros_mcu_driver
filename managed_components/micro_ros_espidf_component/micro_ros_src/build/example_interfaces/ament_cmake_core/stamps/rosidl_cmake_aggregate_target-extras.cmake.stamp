# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target example_interfaces::example_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${example_interfaces_TARGETS}.
if(example_interfaces_TARGETS AND NOT TARGET example_interfaces::example_interfaces)
  add_library(example_interfaces::example_interfaces INTERFACE IMPORTED)
  set_target_properties(example_interfaces::example_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${example_interfaces_TARGETS}")
endif()
