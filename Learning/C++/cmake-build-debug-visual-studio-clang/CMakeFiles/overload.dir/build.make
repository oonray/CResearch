# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\alexa\git\CResearch\Learning\C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang

# Include any dependencies generated for this target.
include CMakeFiles\overload.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\overload.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\overload.dir\flags.make

CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.obj: CMakeFiles\overload.dir\flags.make
CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.obj: ..\basics\Overloading\src\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/overload.dir/basics/Overloading/src/main.cpp.obj"
	C:\PROGRA~1\LLVM\bin\clang-cl.exe @<<
 /nologo -TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\overload.dir\basics\Overloading\src\main.cpp.obj /FdCMakeFiles\overload.dir\ -c C:\Users\alexa\git\CResearch\Learning\C++\basics\Overloading\src\main.cpp
<<

CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/overload.dir/basics/Overloading/src/main.cpp.i"
	C:\PROGRA~1\LLVM\bin\clang-cl.exe > CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.i @<<
 /nologo -TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alexa\git\CResearch\Learning\C++\basics\Overloading\src\main.cpp
<<

CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/overload.dir/basics/Overloading/src/main.cpp.s"
	C:\PROGRA~1\LLVM\bin\clang-cl.exe @<<
 /nologo -TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\overload.dir\basics\Overloading\src\main.cpp.s /c C:\Users\alexa\git\CResearch\Learning\C++\basics\Overloading\src\main.cpp
<<

# Object files for target overload
overload_OBJECTS = \
"CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.obj"

# External object files for target overload
overload_EXTERNAL_OBJECTS =

overload.exe: CMakeFiles\overload.dir\basics\Overloading\src\main.cpp.obj
overload.exe: CMakeFiles\overload.dir\build.make
overload.exe: CMakeFiles\overload.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable overload.exe"
	"C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\overload.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\mt.exe --manifests  -- C:\PROGRA~1\LLVM\bin\lld-link.exe /nologo @CMakeFiles\overload.dir\objects1.rsp @<<
 /out:overload.exe /implib:overload.lib /pdb:C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\overload.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\overload.dir\build: overload.exe

.PHONY : CMakeFiles\overload.dir\build

CMakeFiles\overload.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\overload.dir\cmake_clean.cmake
.PHONY : CMakeFiles\overload.dir\clean

CMakeFiles\overload.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\alexa\git\CResearch\Learning\C++ C:\Users\alexa\git\CResearch\Learning\C++ C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\CMakeFiles\overload.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\overload.dir\depend

