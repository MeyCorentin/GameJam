# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq

# Include any dependencies generated for this target.
include engine/CMakeFiles/r-type_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include engine/CMakeFiles/r-type_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include engine/CMakeFiles/r-type_engine.dir/progress.make

# Include the compile flags for this target's objects.
include engine/CMakeFiles/r-type_engine.dir/flags.make

engine/CMakeFiles/r-type_engine.dir/src/main.cpp.o: engine/CMakeFiles/r-type_engine.dir/flags.make
engine/CMakeFiles/r-type_engine.dir/src/main.cpp.o: engine/src/main.cpp
engine/CMakeFiles/r-type_engine.dir/src/main.cpp.o: engine/CMakeFiles/r-type_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object engine/CMakeFiles/r-type_engine.dir/src/main.cpp.o"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/r-type_engine.dir/src/main.cpp.o -MF CMakeFiles/r-type_engine.dir/src/main.cpp.o.d -o CMakeFiles/r-type_engine.dir/src/main.cpp.o -c /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/src/main.cpp

engine/CMakeFiles/r-type_engine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/r-type_engine.dir/src/main.cpp.i"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/src/main.cpp > CMakeFiles/r-type_engine.dir/src/main.cpp.i

engine/CMakeFiles/r-type_engine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/r-type_engine.dir/src/main.cpp.s"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/src/main.cpp -o CMakeFiles/r-type_engine.dir/src/main.cpp.s

engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o: engine/CMakeFiles/r-type_engine.dir/flags.make
engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o: engine/src/Ecs.cpp
engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o: engine/CMakeFiles/r-type_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o -MF CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o.d -o CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o -c /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/src/Ecs.cpp

engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/r-type_engine.dir/src/Ecs.cpp.i"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/src/Ecs.cpp > CMakeFiles/r-type_engine.dir/src/Ecs.cpp.i

engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/r-type_engine.dir/src/Ecs.cpp.s"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/src/Ecs.cpp -o CMakeFiles/r-type_engine.dir/src/Ecs.cpp.s

# Object files for target r-type_engine
r__type_engine_OBJECTS = \
"CMakeFiles/r-type_engine.dir/src/main.cpp.o" \
"CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o"

# External object files for target r-type_engine
r__type_engine_EXTERNAL_OBJECTS =

engine/r-type_engine: engine/CMakeFiles/r-type_engine.dir/src/main.cpp.o
engine/r-type_engine: engine/CMakeFiles/r-type_engine.dir/src/Ecs.cpp.o
engine/r-type_engine: engine/CMakeFiles/r-type_engine.dir/build.make
engine/r-type_engine: engine/libr-type_library.dylib
engine/r-type_engine: /opt/homebrew/lib/libsfml-graphics.2.5.1.dylib
engine/r-type_engine: /opt/homebrew/lib/libsfml-window.2.5.1.dylib
engine/r-type_engine: /opt/homebrew/lib/libsfml-system.2.5.1.dylib
engine/r-type_engine: engine/CMakeFiles/r-type_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable r-type_engine"
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/r-type_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/CMakeFiles/r-type_engine.dir/build: engine/r-type_engine
.PHONY : engine/CMakeFiles/r-type_engine.dir/build

engine/CMakeFiles/r-type_engine.dir/clean:
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine && $(CMAKE_COMMAND) -P CMakeFiles/r-type_engine.dir/cmake_clean.cmake
.PHONY : engine/CMakeFiles/r-type_engine.dir/clean

engine/CMakeFiles/r-type_engine.dir/depend:
	cd /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine /Users/keziahpcq/Desktop/dev/delivery3/rttype/B-CPP-500-LYN-5-1-rtype-keziah.picq/engine/CMakeFiles/r-type_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : engine/CMakeFiles/r-type_engine.dir/depend

