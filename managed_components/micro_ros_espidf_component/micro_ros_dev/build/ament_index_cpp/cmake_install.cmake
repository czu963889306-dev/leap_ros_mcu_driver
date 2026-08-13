# Install script for directory: /root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/src/ament_index/ament_index_cpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_index_cpp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_package/lib/python3.13/site-packages/ament_package/template/environment_hook/library_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/library_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/ament_index_cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/ament_index_cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/environment" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/local_setup.bash")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/local_setup.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_environment_hooks/package.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_index/share/ament_index/resource_index/packages/ament_index_cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake/export_ament_index_cppExport.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake/export_ament_index_cppExport.cmake"
         "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/CMakeFiles/Export/a4902a30ca177a781c226291a0bd3d0d/export_ament_index_cppExport.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake/export_ament_index_cppExport-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake/export_ament_index_cppExport.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/CMakeFiles/Export/a4902a30ca177a781c226291a0bd3d0d/export_ament_index_cppExport.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/CMakeFiles/Export/a4902a30ca177a781c226291a0bd3d0d/export_ament_index_cppExport-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_export_targets/ament_cmake_export_targets-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp/cmake" TYPE FILE FILES
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_core/ament_index_cppConfig.cmake"
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_cmake_core/ament_index_cppConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/src/ament_index/ament_index_cpp/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ament_index_cpp/ament_index_cpp" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/ament_generate_version_header/ament_index_cpp/ament_index_cpp/version.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ament_index_cpp" TYPE DIRECTORY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/src/ament_index/ament_index_cpp/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libament_index_cpp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libament_index_cpp.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libament_index_cpp.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/libament_index_cpp.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libament_index_cpp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libament_index_cpp.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libament_index_cpp.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/install_local_manifest.txt"
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
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/build/ament_index_cpp/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
