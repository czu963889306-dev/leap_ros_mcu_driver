# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target composition_interfaces::composition_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${composition_interfaces_TARGETS}.
if(composition_interfaces_TARGETS AND NOT TARGET composition_interfaces::composition_interfaces)
  add_library(composition_interfaces::composition_interfaces INTERFACE IMPORTED)
  set_target_properties(composition_interfaces::composition_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${composition_interfaces_TARGETS}")
endif()
