# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /home/jeremy/Desktop/Projects/Source-Playground/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jeremy/Desktop/Projects/Source-Playground/src/build

# Include any dependencies generated for this target.
include raytrace/CMakeFiles/raytrace.dir/depend.make

# Include the progress variables for this target.
include raytrace/CMakeFiles/raytrace.dir/progress.make

# Include the compile flags for this target's objects.
include raytrace/CMakeFiles/raytrace.dir/flags.make

raytrace/CMakeFiles/raytrace.dir/raytrace.cpp.o: raytrace/CMakeFiles/raytrace.dir/flags.make
raytrace/CMakeFiles/raytrace.dir/raytrace.cpp.o: ../raytrace/raytrace.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jeremy/Desktop/Projects/Source-Playground/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object raytrace/CMakeFiles/raytrace.dir/raytrace.cpp.o"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytrace.dir/raytrace.cpp.o -c /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/raytrace.cpp

raytrace/CMakeFiles/raytrace.dir/raytrace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytrace.dir/raytrace.cpp.i"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/raytrace.cpp > CMakeFiles/raytrace.dir/raytrace.cpp.i

raytrace/CMakeFiles/raytrace.dir/raytrace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytrace.dir/raytrace.cpp.s"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/raytrace.cpp -o CMakeFiles/raytrace.dir/raytrace.cpp.s

raytrace/CMakeFiles/raytrace.dir/trace2.cpp.o: raytrace/CMakeFiles/raytrace.dir/flags.make
raytrace/CMakeFiles/raytrace.dir/trace2.cpp.o: ../raytrace/trace2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jeremy/Desktop/Projects/Source-Playground/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object raytrace/CMakeFiles/raytrace.dir/trace2.cpp.o"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytrace.dir/trace2.cpp.o -c /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/trace2.cpp

raytrace/CMakeFiles/raytrace.dir/trace2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytrace.dir/trace2.cpp.i"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/trace2.cpp > CMakeFiles/raytrace.dir/trace2.cpp.i

raytrace/CMakeFiles/raytrace.dir/trace2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytrace.dir/trace2.cpp.s"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/trace2.cpp -o CMakeFiles/raytrace.dir/trace2.cpp.s

raytrace/CMakeFiles/raytrace.dir/trace3.cpp.o: raytrace/CMakeFiles/raytrace.dir/flags.make
raytrace/CMakeFiles/raytrace.dir/trace3.cpp.o: ../raytrace/trace3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jeremy/Desktop/Projects/Source-Playground/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object raytrace/CMakeFiles/raytrace.dir/trace3.cpp.o"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raytrace.dir/trace3.cpp.o -c /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/trace3.cpp

raytrace/CMakeFiles/raytrace.dir/trace3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytrace.dir/trace3.cpp.i"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/trace3.cpp > CMakeFiles/raytrace.dir/trace3.cpp.i

raytrace/CMakeFiles/raytrace.dir/trace3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytrace.dir/trace3.cpp.s"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace/trace3.cpp -o CMakeFiles/raytrace.dir/trace3.cpp.s

# Object files for target raytrace
raytrace_OBJECTS = \
"CMakeFiles/raytrace.dir/raytrace.cpp.o" \
"CMakeFiles/raytrace.dir/trace2.cpp.o" \
"CMakeFiles/raytrace.dir/trace3.cpp.o"

# External object files for target raytrace
raytrace_EXTERNAL_OBJECTS =

raytrace/raytrace.a: raytrace/CMakeFiles/raytrace.dir/raytrace.cpp.o
raytrace/raytrace.a: raytrace/CMakeFiles/raytrace.dir/trace2.cpp.o
raytrace/raytrace.a: raytrace/CMakeFiles/raytrace.dir/trace3.cpp.o
raytrace/raytrace.a: raytrace/CMakeFiles/raytrace.dir/build.make
raytrace/raytrace.a: raytrace/CMakeFiles/raytrace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jeremy/Desktop/Projects/Source-Playground/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library raytrace.a"
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && $(CMAKE_COMMAND) -P CMakeFiles/raytrace.dir/cmake_clean_target.cmake
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytrace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
raytrace/CMakeFiles/raytrace.dir/build: raytrace/raytrace.a

.PHONY : raytrace/CMakeFiles/raytrace.dir/build

raytrace/CMakeFiles/raytrace.dir/clean:
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace && $(CMAKE_COMMAND) -P CMakeFiles/raytrace.dir/cmake_clean.cmake
.PHONY : raytrace/CMakeFiles/raytrace.dir/clean

raytrace/CMakeFiles/raytrace.dir/depend:
	cd /home/jeremy/Desktop/Projects/Source-Playground/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jeremy/Desktop/Projects/Source-Playground/src /home/jeremy/Desktop/Projects/Source-Playground/src/raytrace /home/jeremy/Desktop/Projects/Source-Playground/src/build /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace /home/jeremy/Desktop/Projects/Source-Playground/src/build/raytrace/CMakeFiles/raytrace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : raytrace/CMakeFiles/raytrace.dir/depend

