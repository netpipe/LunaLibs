# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/Dev/libs/csg-stuff/polyvox-0.2.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Dev/libs/csg-stuff/polyvox-0.2.1

# Include any dependencies generated for this target.
include examples/Paging/CMakeFiles/PagingExample.dir/depend.make

# Include the progress variables for this target.
include examples/Paging/CMakeFiles/PagingExample.dir/progress.make

# Include the compile flags for this target's objects.
include examples/Paging/CMakeFiles/PagingExample.dir/flags.make

examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o: examples/Paging/CMakeFiles/PagingExample.dir/flags.make
examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o: examples/Paging/glew/glew.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagingExample.dir/glew/glew.cpp.o -c /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/glew/glew.cpp

examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagingExample.dir/glew/glew.cpp.i"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/glew/glew.cpp > CMakeFiles/PagingExample.dir/glew/glew.cpp.i

examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagingExample.dir/glew/glew.cpp.s"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/glew/glew.cpp -o CMakeFiles/PagingExample.dir/glew/glew.cpp.s

examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.requires:
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.requires

examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.provides: examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.requires
	$(MAKE) -f examples/Paging/CMakeFiles/PagingExample.dir/build.make examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.provides.build
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.provides

examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.provides.build: examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o

examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o: examples/Paging/CMakeFiles/PagingExample.dir/flags.make
examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o: examples/Paging/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagingExample.dir/main.cpp.o -c /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/main.cpp

examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagingExample.dir/main.cpp.i"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/main.cpp > CMakeFiles/PagingExample.dir/main.cpp.i

examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagingExample.dir/main.cpp.s"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/main.cpp -o CMakeFiles/PagingExample.dir/main.cpp.s

examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.requires:
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.requires

examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.provides: examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.requires
	$(MAKE) -f examples/Paging/CMakeFiles/PagingExample.dir/build.make examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.provides.build
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.provides

examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.provides.build: examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o

examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o: examples/Paging/CMakeFiles/PagingExample.dir/flags.make
examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o: examples/Paging/OpenGLWidget.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o -c /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/OpenGLWidget.cpp

examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.i"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/OpenGLWidget.cpp > CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.i

examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.s"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/OpenGLWidget.cpp -o CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.s

examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.requires:
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.requires

examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.provides: examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.requires
	$(MAKE) -f examples/Paging/CMakeFiles/PagingExample.dir/build.make examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.provides.build
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.provides

examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.provides.build: examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o

examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o: examples/Paging/CMakeFiles/PagingExample.dir/flags.make
examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o: examples/Paging/Perlin.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PagingExample.dir/Perlin.cpp.o -c /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/Perlin.cpp

examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PagingExample.dir/Perlin.cpp.i"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/Perlin.cpp > CMakeFiles/PagingExample.dir/Perlin.cpp.i

examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PagingExample.dir/Perlin.cpp.s"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/Perlin.cpp -o CMakeFiles/PagingExample.dir/Perlin.cpp.s

examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.requires:
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.requires

examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.provides: examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.requires
	$(MAKE) -f examples/Paging/CMakeFiles/PagingExample.dir/build.make examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.provides.build
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.provides

examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.provides.build: examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o

# Object files for target PagingExample
PagingExample_OBJECTS = \
"CMakeFiles/PagingExample.dir/glew/glew.cpp.o" \
"CMakeFiles/PagingExample.dir/main.cpp.o" \
"CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o" \
"CMakeFiles/PagingExample.dir/Perlin.cpp.o"

# External object files for target PagingExample
PagingExample_EXTERNAL_OBJECTS =

examples/Paging/PagingExample: examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o
examples/Paging/PagingExample: examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o
examples/Paging/PagingExample: examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o
examples/Paging/PagingExample: examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o
examples/Paging/PagingExample: examples/Paging/CMakeFiles/PagingExample.dir/build.make
examples/Paging/PagingExample: /usr/lib/x86_64-linux-gnu/libQtOpenGL.so
examples/Paging/PagingExample: /usr/lib/x86_64-linux-gnu/libQtGui.so
examples/Paging/PagingExample: /usr/lib/x86_64-linux-gnu/libQtTest.so
examples/Paging/PagingExample: /usr/lib/x86_64-linux-gnu/libQtCore.so
examples/Paging/PagingExample: /usr/lib/x86_64-linux-gnu/libGL.so
examples/Paging/PagingExample: /usr/lib/x86_64-linux-gnu/libGLU.so
examples/Paging/PagingExample: library/PolyVoxCore/libPolyVoxCore.so.0.2.1
examples/Paging/PagingExample: examples/Paging/CMakeFiles/PagingExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable PagingExample"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PagingExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/Paging/CMakeFiles/PagingExample.dir/build: examples/Paging/PagingExample
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/build

examples/Paging/CMakeFiles/PagingExample.dir/requires: examples/Paging/CMakeFiles/PagingExample.dir/glew/glew.cpp.o.requires
examples/Paging/CMakeFiles/PagingExample.dir/requires: examples/Paging/CMakeFiles/PagingExample.dir/main.cpp.o.requires
examples/Paging/CMakeFiles/PagingExample.dir/requires: examples/Paging/CMakeFiles/PagingExample.dir/OpenGLWidget.cpp.o.requires
examples/Paging/CMakeFiles/PagingExample.dir/requires: examples/Paging/CMakeFiles/PagingExample.dir/Perlin.cpp.o.requires
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/requires

examples/Paging/CMakeFiles/PagingExample.dir/clean:
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging && $(CMAKE_COMMAND) -P CMakeFiles/PagingExample.dir/cmake_clean.cmake
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/clean

examples/Paging/CMakeFiles/PagingExample.dir/depend:
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Dev/libs/csg-stuff/polyvox-0.2.1 /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging /home/Dev/libs/csg-stuff/polyvox-0.2.1 /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging /home/Dev/libs/csg-stuff/polyvox-0.2.1/examples/Paging/CMakeFiles/PagingExample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/Paging/CMakeFiles/PagingExample.dir/depend
