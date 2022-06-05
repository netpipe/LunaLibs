# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/netpipe/Dev/LunaLibs/PolyVox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/netpipe/Dev/LunaLibs/PolyVox

# Include any dependencies generated for this target.
include library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/depend.make

# Include the progress variables for this target.
include library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/progress.make

# Include the compile flags for this target's objects.
include library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/flags.make

library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.o: library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/flags.make
library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.o: library/PolyVoxUtil/source/Dummy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/netpipe/Dev/LunaLibs/PolyVox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.o"
	cd /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.o -c /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil/source/Dummy.cpp

library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.i"
	cd /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil/source/Dummy.cpp > CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.i

library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.s"
	cd /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil/source/Dummy.cpp -o CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.s

# Object files for target PolyVoxUtilDynamic
PolyVoxUtilDynamic_OBJECTS = \
"CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.o"

# External object files for target PolyVoxUtilDynamic
PolyVoxUtilDynamic_EXTERNAL_OBJECTS =

library/PolyVoxUtil/libPolyVoxUtil.so.0.1.0: library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/source/Dummy.cpp.o
library/PolyVoxUtil/libPolyVoxUtil.so.0.1.0: library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/build.make
library/PolyVoxUtil/libPolyVoxUtil.so.0.1.0: library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/netpipe/Dev/LunaLibs/PolyVox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libPolyVoxUtil.so"
	cd /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PolyVoxUtilDynamic.dir/link.txt --verbose=$(VERBOSE)
	cd /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil && $(CMAKE_COMMAND) -E cmake_symlink_library libPolyVoxUtil.so.0.1.0 libPolyVoxUtil.so.0 libPolyVoxUtil.so

library/PolyVoxUtil/libPolyVoxUtil.so.0: library/PolyVoxUtil/libPolyVoxUtil.so.0.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate library/PolyVoxUtil/libPolyVoxUtil.so.0

library/PolyVoxUtil/libPolyVoxUtil.so: library/PolyVoxUtil/libPolyVoxUtil.so.0.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate library/PolyVoxUtil/libPolyVoxUtil.so

# Rule to build all files generated by this target.
library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/build: library/PolyVoxUtil/libPolyVoxUtil.so

.PHONY : library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/build

library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/clean:
	cd /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil && $(CMAKE_COMMAND) -P CMakeFiles/PolyVoxUtilDynamic.dir/cmake_clean.cmake
.PHONY : library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/clean

library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/depend:
	cd /home/netpipe/Dev/LunaLibs/PolyVox && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/netpipe/Dev/LunaLibs/PolyVox /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil /home/netpipe/Dev/LunaLibs/PolyVox /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil /home/netpipe/Dev/LunaLibs/PolyVox/library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : library/PolyVoxUtil/CMakeFiles/PolyVoxUtilDynamic.dir/depend

