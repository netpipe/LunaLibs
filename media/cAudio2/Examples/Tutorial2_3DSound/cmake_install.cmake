# Install script for directory: /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Nn][Oo][Nn][Ee]|)$")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound"
           RPATH "")
    endif()
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release" TYPE EXECUTABLE FILES "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/Tutorial1_3DSound")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound"
           OLD_RPATH "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/cAudio:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Release/Tutorial1_3DSound")
      endif()
    endif()
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Nn][Oo][Nn][Ee]|)$")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound"
           RPATH "")
    endif()
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug" TYPE EXECUTABLE FILES "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/Tutorial1_3DSound")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound"
           OLD_RPATH "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/cAudio:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/Debug/Tutorial1_3DSound")
      endif()
    endif()
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound"
           RPATH "")
    endif()
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo" TYPE EXECUTABLE FILES "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/Tutorial1_3DSound")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound"
           OLD_RPATH "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/cAudio:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/RelWithDebInfo/Tutorial1_3DSound")
      endif()
    endif()
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound"
           RPATH "")
    endif()
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel" TYPE EXECUTABLE FILES "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/Tutorial1_3DSound")
    if(EXISTS "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound"
           OLD_RPATH "/home/Dev/libs/Media/cAudio/cAudio-2.1.0/cAudio:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/Dev/libs/Media/cAudio/cAudio-2.1.0/bin/MinSizeRel/Tutorial1_3DSound")
      endif()
    endif()
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
endif()

