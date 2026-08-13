# Install script for directory: /root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/pythonpath.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/pythonpath.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.13/site-packages/rosidl_typesupport_c-2.0.2-py3.13.egg-info" TYPE DIRECTORY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_python/rosidl_typesupport_c/rosidl_typesupport_c.egg-info/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.13/site-packages/rosidl_typesupport_c" TYPE DIRECTORY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c/rosidl_typesupport_c/" REGEX "/[^/]*\\.pyc$" EXCLUDE REGEX "/\\_\\_pycache\\_\\_$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(
        COMMAND
        "/root/.espressif/python_env/idf5.5_py3.13_env/bin/python3" "-m" "compileall"
        "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/install/lib/python3.13/site-packages/rosidl_typesupport_c"
      )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_package/lib/python3.13/site-packages/ament_package/template/environment_hook/library_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/library_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/rosidl_runtime_packages" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_index/share/ament_index/resource_index/rosidl_runtime_packages/rosidl_typesupport_c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/rosidl_typesupport_c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/rosidl_typesupport_c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/local_setup.bash")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/local_setup.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_environment_hooks/package.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_index/share/ament_index/resource_index/packages/rosidl_typesupport_c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake/rosidl_typesupport_cExport.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake/rosidl_typesupport_cExport.cmake"
         "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/CMakeFiles/Export/7ff67efbb2a8228717a4e7abf0a9abcc/rosidl_typesupport_cExport.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake/rosidl_typesupport_cExport-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake/rosidl_typesupport_cExport.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/CMakeFiles/Export/7ff67efbb2a8228717a4e7abf0a9abcc/rosidl_typesupport_cExport.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/CMakeFiles/Export/7ff67efbb2a8228717a4e7abf0a9abcc/rosidl_typesupport_cExport-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_core/rosidl_typesupport_c-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_export_dependencies/ament_cmake_export_dependencies-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_export_include_directories/ament_cmake_export_include_directories-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_export_libraries/ament_cmake_export_libraries-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_export_targets/ament_cmake_export_targets-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c/cmake" TYPE FILE FILES
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_core/rosidl_typesupport_cConfig.cmake"
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/ament_cmake_core/rosidl_typesupport_cConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/rosidl_typesupport_c" TYPE PROGRAM FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c/bin/rosidl_typesupport_c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rosidl_typesupport_c" TYPE DIRECTORY FILES
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c/cmake"
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c/resource"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/rosidl_typesupport_c" TYPE DIRECTORY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/rosidl_typesupport/rosidl_typesupport_c/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/librosidl_typesupport_c.a")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/install_local_manifest.txt"
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
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/rosidl_typesupport_c/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
