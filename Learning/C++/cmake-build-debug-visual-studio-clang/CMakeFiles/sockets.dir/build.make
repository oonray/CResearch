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
include CMakeFiles\sockets.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\sockets.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\sockets.dir\flags.make

CMakeFiles\sockets.dir\sockets\src\main.cpp.obj: CMakeFiles\sockets.dir\flags.make
CMakeFiles\sockets.dir\sockets\src\main.cpp.obj: ..\sockets\src\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sockets.dir/sockets/src/main.cpp.obj"
	C:\PROGRA~1\LLVM\bin\clang-cl.exe @<<
 /nologo -TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\sockets.dir\sockets\src\main.cpp.obj /FdCMakeFiles\sockets.dir\ -c C:\Users\alexa\git\CResearch\Learning\C++\sockets\src\main.cpp
<<

CMakeFiles\sockets.dir\sockets\src\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/sockets/src/main.cpp.i"
	C:\PROGRA~1\LLVM\bin\clang-cl.exe > CMakeFiles\sockets.dir\sockets\src\main.cpp.i @<<
 /nologo -TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\alexa\git\CResearch\Learning\C++\sockets\src\main.cpp
<<

CMakeFiles\sockets.dir\sockets\src\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/sockets/src/main.cpp.s"
	C:\PROGRA~1\LLVM\bin\clang-cl.exe @<<
 /nologo -TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\sockets.dir\sockets\src\main.cpp.s /c C:\Users\alexa\git\CResearch\Learning\C++\sockets\src\main.cpp
<<

# Object files for target sockets
sockets_OBJECTS = \
"CMakeFiles\sockets.dir\sockets\src\main.cpp.obj"

# External object files for target sockets
sockets_EXTERNAL_OBJECTS =

sockets.exe: CMakeFiles\sockets.dir\sockets\src\main.cpp.obj
sockets.exe: CMakeFiles\sockets.dir\build.make
sockets.exe: CMakeFiles\sockets.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sockets.exe"
	"C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\sockets.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\mt.exe --manifests  -- C:\PROGRA~1\LLVM\bin\lld-link.exe /nologo @CMakeFiles\sockets.dir\objects1.rsp @<<
 /out:sockets.exe /implib:sockets.lib /pdb:C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\sockets.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\sockets.dir\build: sockets.exe

.PHONY : CMakeFiles\sockets.dir\build

CMakeFiles\sockets.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\sockets.dir\cmake_clean.cmake
.PHONY : CMakeFiles\sockets.dir\clean

CMakeFiles\sockets.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\alexa\git\CResearch\Learning\C++ C:\Users\alexa\git\CResearch\Learning\C++ C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang C:\Users\alexa\git\CResearch\Learning\C++\cmake-build-debug-visual-studio-clang\CMakeFiles\sockets.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\sockets.dir\depend

