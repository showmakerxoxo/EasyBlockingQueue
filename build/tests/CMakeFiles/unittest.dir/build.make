# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/showmaker/gitspace/EasyBlockingQueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/showmaker/gitspace/EasyBlockingQueue/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/unittest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/unittest.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/unittest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/unittest.dir/flags.make

tests/CMakeFiles/unittest.dir/codegen:
.PHONY : tests/CMakeFiles/unittest.dir/codegen

tests/CMakeFiles/unittest.dir/main.cpp.o: tests/CMakeFiles/unittest.dir/flags.make
tests/CMakeFiles/unittest.dir/main.cpp.o: /Users/showmaker/gitspace/EasyBlockingQueue/tests/main.cpp
tests/CMakeFiles/unittest.dir/main.cpp.o: tests/CMakeFiles/unittest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/showmaker/gitspace/EasyBlockingQueue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/unittest.dir/main.cpp.o"
	cd /Users/showmaker/gitspace/EasyBlockingQueue/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/unittest.dir/main.cpp.o -MF CMakeFiles/unittest.dir/main.cpp.o.d -o CMakeFiles/unittest.dir/main.cpp.o -c /Users/showmaker/gitspace/EasyBlockingQueue/tests/main.cpp

tests/CMakeFiles/unittest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unittest.dir/main.cpp.i"
	cd /Users/showmaker/gitspace/EasyBlockingQueue/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/showmaker/gitspace/EasyBlockingQueue/tests/main.cpp > CMakeFiles/unittest.dir/main.cpp.i

tests/CMakeFiles/unittest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unittest.dir/main.cpp.s"
	cd /Users/showmaker/gitspace/EasyBlockingQueue/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/showmaker/gitspace/EasyBlockingQueue/tests/main.cpp -o CMakeFiles/unittest.dir/main.cpp.s

# Object files for target unittest
unittest_OBJECTS = \
"CMakeFiles/unittest.dir/main.cpp.o"

# External object files for target unittest
unittest_EXTERNAL_OBJECTS =

tests/unittest: tests/CMakeFiles/unittest.dir/main.cpp.o
tests/unittest: tests/CMakeFiles/unittest.dir/build.make
tests/unittest: lib/libgtest.a
tests/unittest: tests/CMakeFiles/unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/showmaker/gitspace/EasyBlockingQueue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable unittest"
	cd /Users/showmaker/gitspace/EasyBlockingQueue/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/unittest.dir/build: tests/unittest
.PHONY : tests/CMakeFiles/unittest.dir/build

tests/CMakeFiles/unittest.dir/clean:
	cd /Users/showmaker/gitspace/EasyBlockingQueue/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/unittest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/unittest.dir/clean

tests/CMakeFiles/unittest.dir/depend:
	cd /Users/showmaker/gitspace/EasyBlockingQueue/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/showmaker/gitspace/EasyBlockingQueue /Users/showmaker/gitspace/EasyBlockingQueue/tests /Users/showmaker/gitspace/EasyBlockingQueue/build /Users/showmaker/gitspace/EasyBlockingQueue/build/tests /Users/showmaker/gitspace/EasyBlockingQueue/build/tests/CMakeFiles/unittest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/unittest.dir/depend

