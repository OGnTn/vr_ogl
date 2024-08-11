# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nate/Downloads/bullet3-3.25

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nate/Downloads/bullet3-3.25

# Include any dependencies generated for this target.
include src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/compiler_depend.make

# Include the progress variables for this target.
include src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/progress.make

# Include the compile flags for this target's objects.
include src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/flags.make

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/flags.make
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.o: src/BulletInverseDynamics/IDMath.cpp
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nate/Downloads/bullet3-3.25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.o"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.o -MF CMakeFiles/BulletInverseDynamics.dir/IDMath.o.d -o CMakeFiles/BulletInverseDynamics.dir/IDMath.o -c /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/IDMath.cpp

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BulletInverseDynamics.dir/IDMath.i"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/IDMath.cpp > CMakeFiles/BulletInverseDynamics.dir/IDMath.i

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BulletInverseDynamics.dir/IDMath.s"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/IDMath.cpp -o CMakeFiles/BulletInverseDynamics.dir/IDMath.s

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/flags.make
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o: src/BulletInverseDynamics/MultiBodyTree.cpp
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nate/Downloads/bullet3-3.25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o -MF CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o.d -o CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o -c /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/MultiBodyTree.cpp

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.i"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/MultiBodyTree.cpp > CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.i

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.s"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/MultiBodyTree.cpp -o CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.s

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/flags.make
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o: src/BulletInverseDynamics/details/MultiBodyTreeInitCache.cpp
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nate/Downloads/bullet3-3.25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o -MF CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o.d -o CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o -c /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/details/MultiBodyTreeInitCache.cpp

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.i"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/details/MultiBodyTreeInitCache.cpp > CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.i

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.s"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/details/MultiBodyTreeInitCache.cpp -o CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.s

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/flags.make
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o: src/BulletInverseDynamics/details/MultiBodyTreeImpl.cpp
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nate/Downloads/bullet3-3.25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o -MF CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o.d -o CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o -c /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/details/MultiBodyTreeImpl.cpp

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.i"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/details/MultiBodyTreeImpl.cpp > CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.i

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.s"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/details/MultiBodyTreeImpl.cpp -o CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.s

# Object files for target BulletInverseDynamics
BulletInverseDynamics_OBJECTS = \
"CMakeFiles/BulletInverseDynamics.dir/IDMath.o" \
"CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o" \
"CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o" \
"CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o"

# External object files for target BulletInverseDynamics
BulletInverseDynamics_EXTERNAL_OBJECTS =

src/BulletInverseDynamics/libBulletInverseDynamics.a: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/IDMath.o
src/BulletInverseDynamics/libBulletInverseDynamics.a: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/MultiBodyTree.o
src/BulletInverseDynamics/libBulletInverseDynamics.a: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeInitCache.o
src/BulletInverseDynamics/libBulletInverseDynamics.a: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/details/MultiBodyTreeImpl.o
src/BulletInverseDynamics/libBulletInverseDynamics.a: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/build.make
src/BulletInverseDynamics/libBulletInverseDynamics.a: src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nate/Downloads/bullet3-3.25/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libBulletInverseDynamics.a"
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && $(CMAKE_COMMAND) -P CMakeFiles/BulletInverseDynamics.dir/cmake_clean_target.cmake
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BulletInverseDynamics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/build: src/BulletInverseDynamics/libBulletInverseDynamics.a
.PHONY : src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/build

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/clean:
	cd /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics && $(CMAKE_COMMAND) -P CMakeFiles/BulletInverseDynamics.dir/cmake_clean.cmake
.PHONY : src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/clean

src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/depend:
	cd /Users/nate/Downloads/bullet3-3.25 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nate/Downloads/bullet3-3.25 /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics /Users/nate/Downloads/bullet3-3.25 /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics /Users/nate/Downloads/bullet3-3.25/src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/BulletInverseDynamics/CMakeFiles/BulletInverseDynamics.dir/depend

