# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /opt/GIT/CResearch/Learning/C/Advanced/CURL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/GIT/CResearch/Learning/C/Advanced/CURL

# Include any dependencies generated for this target.
include CMakeFiles/basiccurl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basiccurl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basiccurl.dir/flags.make

CMakeFiles/basiccurl.dir/src/main.c.o: CMakeFiles/basiccurl.dir/flags.make
CMakeFiles/basiccurl.dir/src/main.c.o: src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/GIT/CResearch/Learning/C/Advanced/CURL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/basiccurl.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/basiccurl.dir/src/main.c.o   -c /opt/GIT/CResearch/Learning/C/Advanced/CURL/src/main.c

CMakeFiles/basiccurl.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/basiccurl.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /opt/GIT/CResearch/Learning/C/Advanced/CURL/src/main.c > CMakeFiles/basiccurl.dir/src/main.c.i

CMakeFiles/basiccurl.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/basiccurl.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /opt/GIT/CResearch/Learning/C/Advanced/CURL/src/main.c -o CMakeFiles/basiccurl.dir/src/main.c.s

# Object files for target basiccurl
basiccurl_OBJECTS = \
"CMakeFiles/basiccurl.dir/src/main.c.o"

# External object files for target basiccurl
basiccurl_EXTERNAL_OBJECTS =

basiccurl: CMakeFiles/basiccurl.dir/src/main.c.o
basiccurl: CMakeFiles/basiccurl.dir/build.make
basiccurl: /usr/lib/x86_64-linux-gnu/libcurl.so
basiccurl: CMakeFiles/basiccurl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/GIT/CResearch/Learning/C/Advanced/CURL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable basiccurl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basiccurl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basiccurl.dir/build: basiccurl

.PHONY : CMakeFiles/basiccurl.dir/build

CMakeFiles/basiccurl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basiccurl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basiccurl.dir/clean

CMakeFiles/basiccurl.dir/depend:
	cd /opt/GIT/CResearch/Learning/C/Advanced/CURL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/GIT/CResearch/Learning/C/Advanced/CURL /opt/GIT/CResearch/Learning/C/Advanced/CURL /opt/GIT/CResearch/Learning/C/Advanced/CURL /opt/GIT/CResearch/Learning/C/Advanced/CURL /opt/GIT/CResearch/Learning/C/Advanced/CURL/CMakeFiles/basiccurl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basiccurl.dir/depend

