# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator"

# Include any dependencies generated for this target.
include CMakeFiles/generator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/generator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/generator.dir/flags.make

CMakeFiles/generator.dir/generator.cpp.o: CMakeFiles/generator.dir/flags.make
CMakeFiles/generator.dir/generator.cpp.o: generator.cpp
CMakeFiles/generator.dir/generator.cpp.o: CMakeFiles/generator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/generator.dir/generator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/generator.dir/generator.cpp.o -MF CMakeFiles/generator.dir/generator.cpp.o.d -o CMakeFiles/generator.dir/generator.cpp.o -c "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator/generator.cpp"

CMakeFiles/generator.dir/generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/generator.dir/generator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator/generator.cpp" > CMakeFiles/generator.dir/generator.cpp.i

CMakeFiles/generator.dir/generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/generator.dir/generator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator/generator.cpp" -o CMakeFiles/generator.dir/generator.cpp.s

# Object files for target generator
generator_OBJECTS = \
"CMakeFiles/generator.dir/generator.cpp.o"

# External object files for target generator
generator_EXTERNAL_OBJECTS =

generator: CMakeFiles/generator.dir/generator.cpp.o
generator: CMakeFiles/generator.dir/build.make
generator: src/Vertice.cpp
generator: src/Bezier.cpp
generator: src/Shape.cpp
generator: src/Plane.cpp
generator: src/Box.cpp
generator: src/Cone.cpp
generator: src/Sphere.cpp
generator: CMakeFiles/generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/generator.dir/build: generator
.PHONY : CMakeFiles/generator.dir/build

CMakeFiles/generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generator.dir/clean

CMakeFiles/generator.dir/depend:
	cd "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_3/generator/CMakeFiles/generator.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/generator.dir/depend

