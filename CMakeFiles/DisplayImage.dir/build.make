# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lilycheng/Desktop/IMAGEPROCESS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lilycheng/Desktop/IMAGEPROCESS

# Include any dependencies generated for this target.
include CMakeFiles/DisplayImage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DisplayImage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DisplayImage.dir/flags.make

CMakeFiles/DisplayImage.dir/ImageProcess.cpp.o: CMakeFiles/DisplayImage.dir/flags.make
CMakeFiles/DisplayImage.dir/ImageProcess.cpp.o: ImageProcess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lilycheng/Desktop/IMAGEPROCESS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DisplayImage.dir/ImageProcess.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DisplayImage.dir/ImageProcess.cpp.o -c /Users/lilycheng/Desktop/IMAGEPROCESS/ImageProcess.cpp

CMakeFiles/DisplayImage.dir/ImageProcess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DisplayImage.dir/ImageProcess.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lilycheng/Desktop/IMAGEPROCESS/ImageProcess.cpp > CMakeFiles/DisplayImage.dir/ImageProcess.cpp.i

CMakeFiles/DisplayImage.dir/ImageProcess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DisplayImage.dir/ImageProcess.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lilycheng/Desktop/IMAGEPROCESS/ImageProcess.cpp -o CMakeFiles/DisplayImage.dir/ImageProcess.cpp.s

# Object files for target DisplayImage
DisplayImage_OBJECTS = \
"CMakeFiles/DisplayImage.dir/ImageProcess.cpp.o"

# External object files for target DisplayImage
DisplayImage_EXTERNAL_OBJECTS =

DisplayImage: CMakeFiles/DisplayImage.dir/ImageProcess.cpp.o
DisplayImage: CMakeFiles/DisplayImage.dir/build.make
DisplayImage: /usr/local/lib/libopencv_dnn.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_gapi.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_highgui.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_ml.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_objdetect.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_photo.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_stitching.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_video.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_videoio.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_imgcodecs.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_calib3d.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_features2d.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_flann.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_imgproc.4.2.0.dylib
DisplayImage: /usr/local/lib/libopencv_core.4.2.0.dylib
DisplayImage: CMakeFiles/DisplayImage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lilycheng/Desktop/IMAGEPROCESS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DisplayImage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DisplayImage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DisplayImage.dir/build: DisplayImage

.PHONY : CMakeFiles/DisplayImage.dir/build

CMakeFiles/DisplayImage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DisplayImage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DisplayImage.dir/clean

CMakeFiles/DisplayImage.dir/depend:
	cd /Users/lilycheng/Desktop/IMAGEPROCESS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lilycheng/Desktop/IMAGEPROCESS /Users/lilycheng/Desktop/IMAGEPROCESS /Users/lilycheng/Desktop/IMAGEPROCESS /Users/lilycheng/Desktop/IMAGEPROCESS /Users/lilycheng/Desktop/IMAGEPROCESS/CMakeFiles/DisplayImage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DisplayImage.dir/depend

