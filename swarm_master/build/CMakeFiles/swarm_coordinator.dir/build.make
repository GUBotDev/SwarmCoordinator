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
CMAKE_SOURCE_DIR = /home/steven/swarm_master/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/steven/swarm_master/build

# Include any dependencies generated for this target.
include CMakeFiles/swarm_coordinator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/swarm_coordinator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/swarm_coordinator.dir/flags.make

CMakeFiles/swarm_coordinator.dir/Main.cpp.o: CMakeFiles/swarm_coordinator.dir/flags.make
CMakeFiles/swarm_coordinator.dir/Main.cpp.o: /home/steven/swarm_master/src/Main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/steven/swarm_master/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/swarm_coordinator.dir/Main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/swarm_coordinator.dir/Main.cpp.o -c /home/steven/swarm_master/src/Main.cpp

CMakeFiles/swarm_coordinator.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/swarm_coordinator.dir/Main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/steven/swarm_master/src/Main.cpp > CMakeFiles/swarm_coordinator.dir/Main.cpp.i

CMakeFiles/swarm_coordinator.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/swarm_coordinator.dir/Main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/steven/swarm_master/src/Main.cpp -o CMakeFiles/swarm_coordinator.dir/Main.cpp.s

CMakeFiles/swarm_coordinator.dir/Main.cpp.o.requires:
.PHONY : CMakeFiles/swarm_coordinator.dir/Main.cpp.o.requires

CMakeFiles/swarm_coordinator.dir/Main.cpp.o.provides: CMakeFiles/swarm_coordinator.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/swarm_coordinator.dir/build.make CMakeFiles/swarm_coordinator.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/swarm_coordinator.dir/Main.cpp.o.provides

CMakeFiles/swarm_coordinator.dir/Main.cpp.o.provides.build: CMakeFiles/swarm_coordinator.dir/Main.cpp.o

# Object files for target swarm_coordinator
swarm_coordinator_OBJECTS = \
"CMakeFiles/swarm_coordinator.dir/Main.cpp.o"

# External object files for target swarm_coordinator
swarm_coordinator_EXTERNAL_OBJECTS =

swarm_coordinator: CMakeFiles/swarm_coordinator.dir/Main.cpp.o
swarm_coordinator: CMakeFiles/swarm_coordinator.dir/build.make
swarm_coordinator: libswarm_coordinator_library.a
swarm_coordinator: CMakeFiles/swarm_coordinator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable swarm_coordinator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/swarm_coordinator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/swarm_coordinator.dir/build: swarm_coordinator
.PHONY : CMakeFiles/swarm_coordinator.dir/build

CMakeFiles/swarm_coordinator.dir/requires: CMakeFiles/swarm_coordinator.dir/Main.cpp.o.requires
.PHONY : CMakeFiles/swarm_coordinator.dir/requires

CMakeFiles/swarm_coordinator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/swarm_coordinator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/swarm_coordinator.dir/clean

CMakeFiles/swarm_coordinator.dir/depend:
	cd /home/steven/swarm_master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/steven/swarm_master/src /home/steven/swarm_master/src /home/steven/swarm_master/build /home/steven/swarm_master/build /home/steven/swarm_master/build/CMakeFiles/swarm_coordinator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/swarm_coordinator.dir/depend

