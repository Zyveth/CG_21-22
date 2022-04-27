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
CMAKE_SOURCE_DIR = "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine"

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/engine.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/engine.cpp.o: engine.cpp
CMakeFiles/engine.dir/engine.cpp.o: CMakeFiles/engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/engine.dir/engine.cpp.o -MF CMakeFiles/engine.dir/engine.cpp.o.d -o CMakeFiles/engine.dir/engine.cpp.o -c "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine/engine.cpp"

CMakeFiles/engine.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine/engine.cpp" > CMakeFiles/engine.dir/engine.cpp.i

CMakeFiles/engine.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine/engine.cpp" -o CMakeFiles/engine.dir/engine.cpp.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/engine.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/engine.cpp.o
engine: CMakeFiles/engine.dir/build.make
engine: src/Vertice.cpp
engine: src/Triangle.cpp
engine: src/Shape.cpp
engine: src/Camera.cpp
engine: src/Parser.cpp
engine: tinyxml2/tinyxml2.cpp
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine
.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine" "/Users/zyveth/Desktop/Universidade/3º Ano/2º Semestre/CG/CG_21-22/Fase_2/engine/CMakeFiles/engine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend

