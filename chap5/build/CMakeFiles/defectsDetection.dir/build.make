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
CMAKE_SOURCE_DIR = "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build"

# Include any dependencies generated for this target.
include CMakeFiles/defectsDetection.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/defectsDetection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/defectsDetection.dir/flags.make

CMakeFiles/defectsDetection.dir/main.cpp.o: CMakeFiles/defectsDetection.dir/flags.make
CMakeFiles/defectsDetection.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/defectsDetection.dir/main.cpp.o"
	/usr/bin/g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/defectsDetection.dir/main.cpp.o -c "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/main.cpp"

CMakeFiles/defectsDetection.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/defectsDetection.dir/main.cpp.i"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/main.cpp" > CMakeFiles/defectsDetection.dir/main.cpp.i

CMakeFiles/defectsDetection.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/defectsDetection.dir/main.cpp.s"
	/usr/bin/g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/main.cpp" -o CMakeFiles/defectsDetection.dir/main.cpp.s

CMakeFiles/defectsDetection.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/defectsDetection.dir/main.cpp.o.requires

CMakeFiles/defectsDetection.dir/main.cpp.o.provides: CMakeFiles/defectsDetection.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/defectsDetection.dir/build.make CMakeFiles/defectsDetection.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/defectsDetection.dir/main.cpp.o.provides

CMakeFiles/defectsDetection.dir/main.cpp.o.provides.build: CMakeFiles/defectsDetection.dir/main.cpp.o


# Object files for target defectsDetection
defectsDetection_OBJECTS = \
"CMakeFiles/defectsDetection.dir/main.cpp.o"

# External object files for target defectsDetection
defectsDetection_EXTERNAL_OBJECTS =

defectsDetection: CMakeFiles/defectsDetection.dir/main.cpp.o
defectsDetection: CMakeFiles/defectsDetection.dir/build.make
defectsDetection: /usr/local/lib/libopencv_dnn.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_gapi.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_highgui.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_ml.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_objdetect.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_photo.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_stitching.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_video.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_videoio.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_imgcodecs.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_calib3d.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_features2d.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_flann.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_imgproc.so.4.5.0
defectsDetection: /usr/local/lib/libopencv_core.so.4.5.0
defectsDetection: CMakeFiles/defectsDetection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable defectsDetection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/defectsDetection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/defectsDetection.dir/build: defectsDetection

.PHONY : CMakeFiles/defectsDetection.dir/build

CMakeFiles/defectsDetection.dir/requires: CMakeFiles/defectsDetection.dir/main.cpp.o.requires

.PHONY : CMakeFiles/defectsDetection.dir/requires

CMakeFiles/defectsDetection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/defectsDetection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/defectsDetection.dir/clean

CMakeFiles/defectsDetection.dir/depend:
	cd "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5" "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5" "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build" "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build" "/home/weihuang/Insync/hweigo@sjtu.edu.cn/OneDrive Biz/ALGO/SLAMBook_Demo/chap5/build/CMakeFiles/defectsDetection.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/defectsDetection.dir/depend

