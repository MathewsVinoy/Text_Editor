# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build

# Include any dependencies generated for this target.
include CMakeFiles/MyTextEditor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyTextEditor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyTextEditor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyTextEditor.dir/flags.make

CMakeFiles/MyTextEditor.dir/src/main.cpp.o: CMakeFiles/MyTextEditor.dir/flags.make
CMakeFiles/MyTextEditor.dir/src/main.cpp.o: /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/main.cpp
CMakeFiles/MyTextEditor.dir/src/main.cpp.o: CMakeFiles/MyTextEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyTextEditor.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTextEditor.dir/src/main.cpp.o -MF CMakeFiles/MyTextEditor.dir/src/main.cpp.o.d -o CMakeFiles/MyTextEditor.dir/src/main.cpp.o -c /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/main.cpp

CMakeFiles/MyTextEditor.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyTextEditor.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/main.cpp > CMakeFiles/MyTextEditor.dir/src/main.cpp.i

CMakeFiles/MyTextEditor.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyTextEditor.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/main.cpp -o CMakeFiles/MyTextEditor.dir/src/main.cpp.s

CMakeFiles/MyTextEditor.dir/src/window.cpp.o: CMakeFiles/MyTextEditor.dir/flags.make
CMakeFiles/MyTextEditor.dir/src/window.cpp.o: /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/window.cpp
CMakeFiles/MyTextEditor.dir/src/window.cpp.o: CMakeFiles/MyTextEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyTextEditor.dir/src/window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTextEditor.dir/src/window.cpp.o -MF CMakeFiles/MyTextEditor.dir/src/window.cpp.o.d -o CMakeFiles/MyTextEditor.dir/src/window.cpp.o -c /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/window.cpp

CMakeFiles/MyTextEditor.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyTextEditor.dir/src/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/window.cpp > CMakeFiles/MyTextEditor.dir/src/window.cpp.i

CMakeFiles/MyTextEditor.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyTextEditor.dir/src/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/src/window.cpp -o CMakeFiles/MyTextEditor.dir/src/window.cpp.s

# Object files for target MyTextEditor
MyTextEditor_OBJECTS = \
"CMakeFiles/MyTextEditor.dir/src/main.cpp.o" \
"CMakeFiles/MyTextEditor.dir/src/window.cpp.o"

# External object files for target MyTextEditor
MyTextEditor_EXTERNAL_OBJECTS =

MyTextEditor: CMakeFiles/MyTextEditor.dir/src/main.cpp.o
MyTextEditor: CMakeFiles/MyTextEditor.dir/src/window.cpp.o
MyTextEditor: CMakeFiles/MyTextEditor.dir/build.make
MyTextEditor: /usr/lib/x86_64-linux-gnu/libSDL2.so
MyTextEditor: CMakeFiles/MyTextEditor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable MyTextEditor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyTextEditor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyTextEditor.dir/build: MyTextEditor
.PHONY : CMakeFiles/MyTextEditor.dir/build

CMakeFiles/MyTextEditor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyTextEditor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyTextEditor.dir/clean

CMakeFiles/MyTextEditor.dir/depend:
	cd /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build /media/mathewsvinoy/820831ee-706c-42e4-8979-f6876adb34d6/dev/Text_Editor/build/CMakeFiles/MyTextEditor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyTextEditor.dir/depend

