# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/nvidia/doushicaji

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nvidia/doushicaji/build

# Include any dependencies generated for this target.
include unittest/serial_test/CMakeFiles/serial_test.dir/depend.make

# Include the progress variables for this target.
include unittest/serial_test/CMakeFiles/serial_test.dir/progress.make

# Include the compile flags for this target's objects.
include unittest/serial_test/CMakeFiles/serial_test.dir/flags.make

unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o: unittest/serial_test/CMakeFiles/serial_test.dir/flags.make
unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o: ../unittest/serial_test/serial_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nvidia/doushicaji/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o"
	cd /home/nvidia/doushicaji/build/unittest/serial_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial_test.dir/serial_test.cpp.o -c /home/nvidia/doushicaji/unittest/serial_test/serial_test.cpp

unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_test.dir/serial_test.cpp.i"
	cd /home/nvidia/doushicaji/build/unittest/serial_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nvidia/doushicaji/unittest/serial_test/serial_test.cpp > CMakeFiles/serial_test.dir/serial_test.cpp.i

unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_test.dir/serial_test.cpp.s"
	cd /home/nvidia/doushicaji/build/unittest/serial_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nvidia/doushicaji/unittest/serial_test/serial_test.cpp -o CMakeFiles/serial_test.dir/serial_test.cpp.s

unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.requires:

.PHONY : unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.requires

unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.provides: unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.requires
	$(MAKE) -f unittest/serial_test/CMakeFiles/serial_test.dir/build.make unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.provides.build
.PHONY : unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.provides

unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.provides.build: unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o


# Object files for target serial_test
serial_test_OBJECTS = \
"CMakeFiles/serial_test.dir/serial_test.cpp.o"

# External object files for target serial_test
serial_test_EXTERNAL_OBJECTS =

unittest/serial_test/serial_test: unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o
unittest/serial_test/serial_test: unittest/serial_test/CMakeFiles/serial_test.dir/build.make
unittest/serial_test/serial_test: libHardWare/serialPort/libSerialPort.a
unittest/serial_test/serial_test: libBase/libBase.a
unittest/serial_test/serial_test: osdk-core/libdjiosdk-core.a
unittest/serial_test/serial_test: libLinuxHelper.a
unittest/serial_test/serial_test: /usr/lib/libopencv_dnn.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_ml.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_objdetect.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_shape.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_stitching.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_superres.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_videostab.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_calib3d.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_features2d.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_flann.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_highgui.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_photo.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_video.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_videoio.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_imgcodecs.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_imgproc.so.3.3.1
unittest/serial_test/serial_test: /usr/lib/libopencv_core.so.3.3.1
unittest/serial_test/serial_test: unittest/serial_test/CMakeFiles/serial_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nvidia/doushicaji/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable serial_test"
	cd /home/nvidia/doushicaji/build/unittest/serial_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unittest/serial_test/CMakeFiles/serial_test.dir/build: unittest/serial_test/serial_test

.PHONY : unittest/serial_test/CMakeFiles/serial_test.dir/build

unittest/serial_test/CMakeFiles/serial_test.dir/requires: unittest/serial_test/CMakeFiles/serial_test.dir/serial_test.cpp.o.requires

.PHONY : unittest/serial_test/CMakeFiles/serial_test.dir/requires

unittest/serial_test/CMakeFiles/serial_test.dir/clean:
	cd /home/nvidia/doushicaji/build/unittest/serial_test && $(CMAKE_COMMAND) -P CMakeFiles/serial_test.dir/cmake_clean.cmake
.PHONY : unittest/serial_test/CMakeFiles/serial_test.dir/clean

unittest/serial_test/CMakeFiles/serial_test.dir/depend:
	cd /home/nvidia/doushicaji/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nvidia/doushicaji /home/nvidia/doushicaji/unittest/serial_test /home/nvidia/doushicaji/build /home/nvidia/doushicaji/build/unittest/serial_test /home/nvidia/doushicaji/build/unittest/serial_test/CMakeFiles/serial_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unittest/serial_test/CMakeFiles/serial_test.dir/depend

