# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/sandesh/Downloads/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/sandesh/Downloads/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sandesh/projects/blockenger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sandesh/projects/blockenger/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gtkmmproject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gtkmmproject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtkmmproject.dir/flags.make

CMakeFiles/gtkmmproject.dir/main.cpp.o: CMakeFiles/gtkmmproject.dir/flags.make
CMakeFiles/gtkmmproject.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sandesh/projects/blockenger/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gtkmmproject.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtkmmproject.dir/main.cpp.o -c /home/sandesh/projects/blockenger/main.cpp

CMakeFiles/gtkmmproject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtkmmproject.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sandesh/projects/blockenger/main.cpp > CMakeFiles/gtkmmproject.dir/main.cpp.i

CMakeFiles/gtkmmproject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtkmmproject.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sandesh/projects/blockenger/main.cpp -o CMakeFiles/gtkmmproject.dir/main.cpp.s

CMakeFiles/gtkmmproject.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/gtkmmproject.dir/main.cpp.o.requires

CMakeFiles/gtkmmproject.dir/main.cpp.o.provides: CMakeFiles/gtkmmproject.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/gtkmmproject.dir/build.make CMakeFiles/gtkmmproject.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/gtkmmproject.dir/main.cpp.o.provides

CMakeFiles/gtkmmproject.dir/main.cpp.o.provides.build: CMakeFiles/gtkmmproject.dir/main.cpp.o


# Object files for target gtkmmproject
gtkmmproject_OBJECTS = \
"CMakeFiles/gtkmmproject.dir/main.cpp.o"

# External object files for target gtkmmproject
gtkmmproject_EXTERNAL_OBJECTS =

gtkmmproject: CMakeFiles/gtkmmproject.dir/main.cpp.o
gtkmmproject: CMakeFiles/gtkmmproject.dir/build.make
gtkmmproject: CMakeFiles/gtkmmproject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sandesh/projects/blockenger/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gtkmmproject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtkmmproject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtkmmproject.dir/build: gtkmmproject

.PHONY : CMakeFiles/gtkmmproject.dir/build

CMakeFiles/gtkmmproject.dir/requires: CMakeFiles/gtkmmproject.dir/main.cpp.o.requires

.PHONY : CMakeFiles/gtkmmproject.dir/requires

CMakeFiles/gtkmmproject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gtkmmproject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gtkmmproject.dir/clean

CMakeFiles/gtkmmproject.dir/depend:
	cd /home/sandesh/projects/blockenger/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sandesh/projects/blockenger /home/sandesh/projects/blockenger /home/sandesh/projects/blockenger/cmake-build-debug /home/sandesh/projects/blockenger/cmake-build-debug /home/sandesh/projects/blockenger/cmake-build-debug/CMakeFiles/gtkmmproject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtkmmproject.dir/depend

