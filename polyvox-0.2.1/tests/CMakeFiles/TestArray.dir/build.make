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
include tests/CMakeFiles/TestArray.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/TestArray.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/TestArray.dir/flags.make

tests/moc_TestArray.cxx: tests/TestArray.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_TestArray.cxx"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/moc-qt4 -I/usr/include/qt4 -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtCore -I/home/Dev/libs/csg-stuff/polyvox-0.2.1/library/PolyVoxCore/include -I/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_TEST_LIB -DQT_CORE_LIB -o /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/moc_TestArray.cxx /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestArray.h

tests/CMakeFiles/TestArray.dir/TestArray.cpp.o: tests/CMakeFiles/TestArray.dir/flags.make
tests/CMakeFiles/TestArray.dir/TestArray.cpp.o: tests/TestArray.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tests/CMakeFiles/TestArray.dir/TestArray.cpp.o"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestArray.dir/TestArray.cpp.o -c /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestArray.cpp

tests/CMakeFiles/TestArray.dir/TestArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestArray.dir/TestArray.cpp.i"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestArray.cpp > CMakeFiles/TestArray.dir/TestArray.cpp.i

tests/CMakeFiles/TestArray.dir/TestArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestArray.dir/TestArray.cpp.s"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestArray.cpp -o CMakeFiles/TestArray.dir/TestArray.cpp.s

tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.requires:
.PHONY : tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.requires

tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.provides: tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/TestArray.dir/build.make tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.provides.build
.PHONY : tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.provides

tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.provides.build: tests/CMakeFiles/TestArray.dir/TestArray.cpp.o

tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o: tests/CMakeFiles/TestArray.dir/flags.make
tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o: tests/moc_TestArray.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/Dev/libs/csg-stuff/polyvox-0.2.1/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestArray.dir/moc_TestArray.cxx.o -c /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/moc_TestArray.cxx

tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestArray.dir/moc_TestArray.cxx.i"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/moc_TestArray.cxx > CMakeFiles/TestArray.dir/moc_TestArray.cxx.i

tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestArray.dir/moc_TestArray.cxx.s"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/moc_TestArray.cxx -o CMakeFiles/TestArray.dir/moc_TestArray.cxx.s

tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.requires:
.PHONY : tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.requires

tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.provides: tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.requires
	$(MAKE) -f tests/CMakeFiles/TestArray.dir/build.make tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.provides.build
.PHONY : tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.provides

tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.provides.build: tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o

# Object files for target TestArray
TestArray_OBJECTS = \
"CMakeFiles/TestArray.dir/TestArray.cpp.o" \
"CMakeFiles/TestArray.dir/moc_TestArray.cxx.o"

# External object files for target TestArray
TestArray_EXTERNAL_OBJECTS =

tests/TestArray: tests/CMakeFiles/TestArray.dir/TestArray.cpp.o
tests/TestArray: tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o
tests/TestArray: tests/CMakeFiles/TestArray.dir/build.make
tests/TestArray: library/PolyVoxCore/libPolyVoxCore.so.0.2.1
tests/TestArray: library/PolyVoxUtil/libPolyVoxUtil.so.0.2.1
tests/TestArray: /usr/lib/x86_64-linux-gnu/libQtTest.so
tests/TestArray: /usr/lib/x86_64-linux-gnu/libQtCore.so
tests/TestArray: library/PolyVoxCore/libPolyVoxCore.so.0.2.1
tests/TestArray: tests/CMakeFiles/TestArray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TestArray"
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestArray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/TestArray.dir/build: tests/TestArray
.PHONY : tests/CMakeFiles/TestArray.dir/build

tests/CMakeFiles/TestArray.dir/requires: tests/CMakeFiles/TestArray.dir/TestArray.cpp.o.requires
tests/CMakeFiles/TestArray.dir/requires: tests/CMakeFiles/TestArray.dir/moc_TestArray.cxx.o.requires
.PHONY : tests/CMakeFiles/TestArray.dir/requires

tests/CMakeFiles/TestArray.dir/clean:
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests && $(CMAKE_COMMAND) -P CMakeFiles/TestArray.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/TestArray.dir/clean

tests/CMakeFiles/TestArray.dir/depend: tests/moc_TestArray.cxx
	cd /home/Dev/libs/csg-stuff/polyvox-0.2.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Dev/libs/csg-stuff/polyvox-0.2.1 /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests /home/Dev/libs/csg-stuff/polyvox-0.2.1 /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/CMakeFiles/TestArray.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/TestArray.dir/depend

