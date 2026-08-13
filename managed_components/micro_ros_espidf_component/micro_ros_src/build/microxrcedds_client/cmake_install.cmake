# Install script for directory: /root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/Micro-XRCE-DDS-Client

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "libraries" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/libmicroxrcedds_client.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uxr/client" TYPE DIRECTORY FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/src/Micro-XRCE-DDS-Client/include/uxr/client/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uxr/client" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/include/uxr/client/config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake/microxrcedds_clientTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake/microxrcedds_clientTargets.cmake"
         "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/CMakeFiles/Export/6d9d903bcaa9f45eb38e19ffccdfdae9/microxrcedds_clientTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake/microxrcedds_clientTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake/microxrcedds_clientTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/CMakeFiles/Export/6d9d903bcaa9f45eb38e19ffccdfdae9/microxrcedds_clientTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake" TYPE FILE FILES "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/CMakeFiles/Export/6d9d903bcaa9f45eb38e19ffccdfdae9/microxrcedds_clientTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/microxrcedds_client/cmake" TYPE FILE FILES
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/cmake/config/microxrcedds_clientConfig.cmake"
    "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/cmake/config/microxrcedds_clientConfigVersion.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/install_local_manifest.txt"
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
  file(WRITE "/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_src/build/microxrcedds_client/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
