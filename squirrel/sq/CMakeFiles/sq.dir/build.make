# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel

# Include any dependencies generated for this target.
include sq/CMakeFiles/sq.dir/depend.make

# Include the progress variables for this target.
include sq/CMakeFiles/sq.dir/progress.make

# Include the compile flags for this target's objects.
include sq/CMakeFiles/sq.dir/flags.make

sq/CMakeFiles/sq.dir/sq.c.o: sq/CMakeFiles/sq.dir/flags.make
sq/CMakeFiles/sq.dir/sq.c.o: sq/sq.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object sq/CMakeFiles/sq.dir/sq.c.o"
	cd /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sq.dir/sq.c.o   -c /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq/sq.c

sq/CMakeFiles/sq.dir/sq.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sq.dir/sq.c.i"
	cd /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq/sq.c > CMakeFiles/sq.dir/sq.c.i

sq/CMakeFiles/sq.dir/sq.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sq.dir/sq.c.s"
	cd /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq/sq.c -o CMakeFiles/sq.dir/sq.c.s

sq/CMakeFiles/sq.dir/sq.c.o.requires:

.PHONY : sq/CMakeFiles/sq.dir/sq.c.o.requires

sq/CMakeFiles/sq.dir/sq.c.o.provides: sq/CMakeFiles/sq.dir/sq.c.o.requires
	$(MAKE) -f sq/CMakeFiles/sq.dir/build.make sq/CMakeFiles/sq.dir/sq.c.o.provides.build
.PHONY : sq/CMakeFiles/sq.dir/sq.c.o.provides

sq/CMakeFiles/sq.dir/sq.c.o.provides.build: sq/CMakeFiles/sq.dir/sq.c.o


# Object files for target sq
sq_OBJECTS = \
"CMakeFiles/sq.dir/sq.c.o"

# External object files for target sq
sq_EXTERNAL_OBJECTS =

bin/sq: sq/CMakeFiles/sq.dir/sq.c.o
bin/sq: sq/CMakeFiles/sq.dir/build.make
bin/sq: lib64/libsqstdlib.so.0.0.0
bin/sq: lib64/libsquirrel.so.0.0.0
bin/sq: sq/CMakeFiles/sq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/sq"
	cd /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sq/CMakeFiles/sq.dir/build: bin/sq

.PHONY : sq/CMakeFiles/sq.dir/build

sq/CMakeFiles/sq.dir/requires: sq/CMakeFiles/sq.dir/sq.c.o.requires

.PHONY : sq/CMakeFiles/sq.dir/requires

sq/CMakeFiles/sq.dir/clean:
	cd /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq && $(CMAKE_COMMAND) -P CMakeFiles/sq.dir/cmake_clean.cmake
.PHONY : sq/CMakeFiles/sq.dir/clean

sq/CMakeFiles/sq.dir/depend:
	cd /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq /run/media/netpipe/df7f53ef-2a98-4562-a498-7da578dab660/games/Luna/LunaLibs-current/squirrel/sq/CMakeFiles/sq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sq/CMakeFiles/sq.dir/depend

