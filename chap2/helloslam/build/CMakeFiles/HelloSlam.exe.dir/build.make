# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/weihuang/slambook/chap2/helloslam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/weihuang/slambook/chap2/helloslam/build

# Include any dependencies generated for this target.
include CMakeFiles/HelloSlam.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloSlam.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloSlam.exe.dir/flags.make

CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o: CMakeFiles/HelloSlam.exe.dir/flags.make
CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o: ../helloSlam.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/weihuang/slambook/chap2/helloslam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o -c /home/weihuang/slambook/chap2/helloslam/helloSlam.cpp

CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/weihuang/slambook/chap2/helloslam/helloSlam.cpp > CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.i

CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/weihuang/slambook/chap2/helloslam/helloSlam.cpp -o CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.s

CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.requires:

.PHONY : CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.requires

CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.provides: CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.requires
	$(MAKE) -f CMakeFiles/HelloSlam.exe.dir/build.make CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.provides.build
.PHONY : CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.provides

CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.provides.build: CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o


# Object files for target HelloSlam.exe
HelloSlam_exe_OBJECTS = \
"CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o"

# External object files for target HelloSlam.exe
HelloSlam_exe_EXTERNAL_OBJECTS =

HelloSlam.exe: CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o
HelloSlam.exe: CMakeFiles/HelloSlam.exe.dir/build.make
HelloSlam.exe: CMakeFiles/HelloSlam.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/weihuang/slambook/chap2/helloslam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HelloSlam.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloSlam.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HelloSlam.exe.dir/build: HelloSlam.exe

.PHONY : CMakeFiles/HelloSlam.exe.dir/build

CMakeFiles/HelloSlam.exe.dir/requires: CMakeFiles/HelloSlam.exe.dir/helloSlam.cpp.o.requires

.PHONY : CMakeFiles/HelloSlam.exe.dir/requires

CMakeFiles/HelloSlam.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloSlam.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloSlam.exe.dir/clean

CMakeFiles/HelloSlam.exe.dir/depend:
	cd /home/weihuang/slambook/chap2/helloslam/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/weihuang/slambook/chap2/helloslam /home/weihuang/slambook/chap2/helloslam /home/weihuang/slambook/chap2/helloslam/build /home/weihuang/slambook/chap2/helloslam/build /home/weihuang/slambook/chap2/helloslam/build/CMakeFiles/HelloSlam.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HelloSlam.exe.dir/depend

