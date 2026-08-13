# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target std_srvs::std_srvs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${std_srvs_TARGETS}.
if(std_srvs_TARGETS AND NOT TARGET std_srvs::std_srvs)
  add_library(std_srvs::std_srvs INTERFACE IMPORTED)
  set_target_properties(std_srvs::std_srvs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${std_srvs_TARGETS}")
endif()
