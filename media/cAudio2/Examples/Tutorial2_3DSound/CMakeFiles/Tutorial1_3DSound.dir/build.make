# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_SOURCE_DIR = /home/Dev/libs/Media/cAudio/cAudio-2.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Dev/libs/Media/cAudio/cAudio-2.1.0

# Include any dependencies generated for this target.
include Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/depend.make

# Include the progress variables for this target.
include Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/progress.make

# Include the compile flags for this target's objects.
include Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/flags.make

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/flags.make
Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o: Examples/Tutorial2_3DSound/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Dev/libs/Media/cAudio/cAudio-2.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o"
	cd /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o -c /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/src/main.cpp

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.i"
	cd /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/src/main.cpp > CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.i

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.s"
	cd /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/src/main.cpp -o CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.s

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.requires:

.PHONY : Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.requires

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.provides: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.requires
	$(MAKE) -f Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/build.make Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.provides.build
.PHONY : Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.provides

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.provides.build: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o


# Object files for target Tutorial1_3DSound
Tutorial1_3DSound_OBJECTS = \
"CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o"

# External object files for target Tutorial1_3DSound
Tutorial1_3DSound_EXTERNAL_OBJECTS =

Examples/Tutorial2_3DSound/Tutorial1_3DSound: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o
Examples/Tutorial2_3DSound/Tutorial1_3DSound: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/build.make
Examples/Tutorial2_3DSound/Tutorial1_3DSound: cAudio/libcAudio.so
Examples/Tutorial2_3DSound/Tutorial1_3DSound: DependenciesSource/libvorbis-1.3.2/libVorbis.a
Examples/Tutorial2_3DSound/Tutorial1_3DSound: DependenciesSource/libogg-1.2.2/libOgg.a
Examples/Tutorial2_3DSound/Tutorial1_3DSound: /usr/lib64/libopenal.so
Examples/Tutorial2_3DSound/Tutorial1_3DSound: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Dev/libs/Media/cAudio/cAudio-2.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tutorial1_3DSound"
	cd /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tutorial1_3DSound.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/build: Examples/Tutorial2_3DSound/Tutorial1_3DSound

.PHONY : Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/build

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/requires: Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/src/main.cpp.o.requires

.PHONY : Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/requires

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/clean:
	cd /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound && $(CMAKE_COMMAND) -P CMakeFiles/Tutorial1_3DSound.dir/cmake_clean.cmake
.PHONY : Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/clean

Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/depend:
	cd /home/Dev/libs/Media/cAudio/cAudio-2.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Dev/libs/Media/cAudio/cAudio-2.1.0 /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound /home/Dev/libs/Media/cAudio/cAudio-2.1.0 /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound /home/Dev/libs/Media/cAudio/cAudio-2.1.0/Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Examples/Tutorial2_3DSound/CMakeFiles/Tutorial1_3DSound.dir/depend

