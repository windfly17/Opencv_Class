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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Desktop\Opencv_Class\class_9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Desktop\Opencv_Class\class_9\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\class_9.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\class_9.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\class_9.dir\flags.make

CMakeFiles\class_9.dir\hog.cpp.obj: CMakeFiles\class_9.dir\flags.make
CMakeFiles\class_9.dir\hog.cpp.obj: ..\hog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Desktop\Opencv_Class\class_9\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class_9.dir/hog.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\class_9.dir\hog.cpp.obj /FdCMakeFiles\class_9.dir\ /FS -c D:\Desktop\Opencv_Class\class_9\hog.cpp
<<

CMakeFiles\class_9.dir\hog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class_9.dir/hog.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe > CMakeFiles\class_9.dir\hog.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Desktop\Opencv_Class\class_9\hog.cpp
<<

CMakeFiles\class_9.dir\hog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class_9.dir/hog.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\class_9.dir\hog.cpp.s /c D:\Desktop\Opencv_Class\class_9\hog.cpp
<<

# Object files for target class_9
class_9_OBJECTS = \
"CMakeFiles\class_9.dir\hog.cpp.obj"

# External object files for target class_9
class_9_EXTERNAL_OBJECTS =

class_9.exe: CMakeFiles\class_9.dir\hog.cpp.obj
class_9.exe: CMakeFiles\class_9.dir\build.make
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib
class_9.exe: CMakeFiles\class_9.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Desktop\Opencv_Class\class_9\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class_9.exe"
	"C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\class_9.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\class_9.dir\objects1.rsp @<<
 /out:class_9.exe /implib:class_9.lib /pdb:D:\Desktop\Opencv_Class\class_9\cmake-build-debug\class_9.pdb /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console  D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib D:\Opencv_4.3.0\opencv\build\x64\vc15\lib\opencv_world430d.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\class_9.dir\build: class_9.exe

.PHONY : CMakeFiles\class_9.dir\build

CMakeFiles\class_9.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\class_9.dir\cmake_clean.cmake
.PHONY : CMakeFiles\class_9.dir\clean

CMakeFiles\class_9.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Desktop\Opencv_Class\class_9 D:\Desktop\Opencv_Class\class_9 D:\Desktop\Opencv_Class\class_9\cmake-build-debug D:\Desktop\Opencv_Class\class_9\cmake-build-debug D:\Desktop\Opencv_Class\class_9\cmake-build-debug\CMakeFiles\class_9.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\class_9.dir\depend

