# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_DEB "OFF")
set(CPACK_BINARY_FREEBSD "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "OFF")
set(CPACK_BINARY_RPM "OFF")
set(CPACK_BINARY_STGZ "ON")
set(CPACK_BINARY_TBZ2 "OFF")
set(CPACK_BINARY_TGZ "ON")
set(CPACK_BINARY_TXZ "OFF")
set(CPACK_BINARY_TZ "ON")
set(CPACK_BUILD_SOURCE_DIRS "/home/netpipe/gamedev/LunaLibs/polyvox-0.2.1;/home/netpipe/gamedev/LunaLibs/polyvox-0.2.1")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "development;library")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "PolyVox built using CMake")
set(CPACK_GENERATOR "STGZ;TGZ;TZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/netpipe/gamedev/LunaLibs/polyvox-0.2.1;PolyVox;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "PolyVox SDK 0.2.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "PolyVox SDK 0.2.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/netpipe/gamedev/LunaLibs/polyvox-0.2.1/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PolyVox SDK")
set(CPACK_PACKAGE_FILE_NAME "PolyVox SDK-0.2.1-Linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "PolyVox SDK 0.2.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "PolyVox SDK 0.2.1")
set(CPACK_PACKAGE_NAME "PolyVox SDK")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Thermite 3D Team")
set(CPACK_PACKAGE_VERSION "0.2.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/share/cmake/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/netpipe/gamedev/LunaLibs/polyvox-0.2.1/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/netpipe/gamedev/LunaLibs/polyvox-0.2.1/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

# Configuration for component "library"

SET(CPACK_COMPONENTS_ALL development library)
set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Library")
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "The runtime libraries")
set(CPACK_COMPONENT_LIBRARY_REQUIRED TRUE)

# Configuration for component "development"

SET(CPACK_COMPONENTS_ALL development library)
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development")
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Files required for developing with PolyVox")
set(CPACK_COMPONENT_DEVELOPMENT_DEPENDS library)

# Configuration for component "example"

SET(CPACK_COMPONENTS_ALL development library)
set(CPACK_COMPONENT_EXAMPLE_DISPLAY_NAME "OpenGL Example")
set(CPACK_COMPONENT_EXAMPLE_DESCRIPTION "A PolyVox example application using OpenGL")
set(CPACK_COMPONENT_EXAMPLE_DEPENDS library)

# Configuration for component group "bindings"
set(CPACK_COMPONENT_GROUP_BINDINGS_DISPLAY_NAME "Bindings")
set(CPACK_COMPONENT_GROUP_BINDINGS_DESCRIPTION "Language bindings")

# Configuration for component "python"

SET(CPACK_COMPONENTS_ALL development library)
set(CPACK_COMPONENT_PYTHON_DISPLAY_NAME "Python Bindings")
set(CPACK_COMPONENT_PYTHON_DESCRIPTION "PolyVox bindings for the Python language")
set(CPACK_COMPONENT_PYTHON_GROUP bindings)
set(CPACK_COMPONENT_PYTHON_DEPENDS library)
set(CPACK_COMPONENT_PYTHON_DISABLED TRUE)
