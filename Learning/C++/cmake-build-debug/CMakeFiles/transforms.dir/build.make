# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/oonray/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/203.4818.55/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/oonray/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/203.4818.55/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oonray/git/CResearch/Learning/C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oonray/git/CResearch/Learning/C++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/transforms.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/transforms.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/transforms.dir/flags.make

CMakeFiles/transforms.dir/Transforms/src/main.cpp.o: CMakeFiles/transforms.dir/flags.make
CMakeFiles/transforms.dir/Transforms/src/main.cpp.o: ../Transforms/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oonray/git/CResearch/Learning/C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/transforms.dir/Transforms/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/transforms.dir/Transforms/src/main.cpp.o -c /home/oonray/git/CResearch/Learning/C++/Transforms/src/main.cpp

CMakeFiles/transforms.dir/Transforms/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/transforms.dir/Transforms/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oonray/git/CResearch/Learning/C++/Transforms/src/main.cpp > CMakeFiles/transforms.dir/Transforms/src/main.cpp.i

CMakeFiles/transforms.dir/Transforms/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/transforms.dir/Transforms/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oonray/git/CResearch/Learning/C++/Transforms/src/main.cpp -o CMakeFiles/transforms.dir/Transforms/src/main.cpp.s

# Object files for target transforms
transforms_OBJECTS = \
"CMakeFiles/transforms.dir/Transforms/src/main.cpp.o"

# External object files for target transforms
transforms_EXTERNAL_OBJECTS =

bin/transforms: CMakeFiles/transforms.dir/Transforms/src/main.cpp.o
bin/transforms: CMakeFiles/transforms.dir/build.make
bin/transforms: CMakeFiles/transforms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oonray/git/CResearch/Learning/C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/transforms"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/transforms.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/transforms.dir/build: bin/transforms

.PHONY : CMakeFiles/transforms.dir/build

CMakeFiles/transforms.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/transforms.dir/cmake_clean.cmake
.PHONY : CMakeFiles/transforms.dir/clean

CMakeFiles/transforms.dir/depend:
	cd /home/oonray/git/CResearch/Learning/C++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oonray/git/CResearch/Learning/C++ /home/oonray/git/CResearch/Learning/C++ /home/oonray/git/CResearch/Learning/C++/cmake-build-debug /home/oonray/git/CResearch/Learning/C++/cmake-build-debug /home/oonray/git/CResearch/Learning/C++/cmake-build-debug/CMakeFiles/transforms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/transforms.dir/depend

