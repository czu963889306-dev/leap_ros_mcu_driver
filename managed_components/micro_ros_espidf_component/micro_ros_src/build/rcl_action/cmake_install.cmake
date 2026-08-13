# Install script for directory: /root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rcl/rcl_action

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "1")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/root/.espressif/tools/xtensa-esp-elf/esp-14.2.0_20251107/xtensa-esp-elf/bin/xtensa-esp32s3-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/rcl_action" TYPE DIRECTORY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rcl/rcl_action/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/librcl_action.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_package/lib/python3.13/site-packages/ament_package/template/environment_hook/library_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/library_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/rcl_action/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_generate_version_header/rcl_action/rcl_action/version.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/rcl_action")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/rcl_action")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/local_setup.bash")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/local_setup.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_environment_hooks/package.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_index/share/ament_index/resource_index/packages/rcl_action")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake/rcl_actionExport.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake/rcl_actionExport.cmake"
         "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/CMakeFiles/Export/0c99ed9b5f911e1e7dcd5248d57734ef/rcl_actionExport.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake/rcl_actionExport-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake/rcl_actionExport.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/CMakeFiles/Export/0c99ed9b5f911e1e7dcd5248d57734ef/rcl_actionExport.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/CMakeFiles/Export/0c99ed9b5f911e1e7dcd5248d57734ef/rcl_actionExport-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_export_include_directories/ament_cmake_export_include_directories-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_export_libraries/ament_cmake_export_libraries-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_export_targets/ament_cmake_export_targets-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_export_dependencies/ament_cmake_export_dependencies-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action/cmake" TYPE FILE FILES
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_core/rcl_actionConfig.cmake"
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/ament_cmake_core/rcl_actionConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rcl_action" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rcl/rcl_action/package.xml")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rcl_action/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
