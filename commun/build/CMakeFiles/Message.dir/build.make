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
CMAKE_COMMAND = /usr/local/opt/cmake-3.26.3/bin/cmake

# The command to remove a file.
RM = /usr/local/opt/cmake-3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /export/tmp/4205_34/ele4205_projet_aut2023_34/commun

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build

# Include any dependencies generated for this target.
include CMakeFiles/Message.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Message.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Message.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Message.dir/flags.make

CMakeFiles/Message.dir/message.cpp.o: CMakeFiles/Message.dir/flags.make
CMakeFiles/Message.dir/message.cpp.o: /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/message.cpp
CMakeFiles/Message.dir/message.cpp.o: CMakeFiles/Message.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Message.dir/message.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Message.dir/message.cpp.o -MF CMakeFiles/Message.dir/message.cpp.o.d -o CMakeFiles/Message.dir/message.cpp.o -c /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/message.cpp

CMakeFiles/Message.dir/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Message.dir/message.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/message.cpp > CMakeFiles/Message.dir/message.cpp.i

CMakeFiles/Message.dir/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Message.dir/message.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/message.cpp -o CMakeFiles/Message.dir/message.cpp.s

# Object files for target Message
Message_OBJECTS = \
"CMakeFiles/Message.dir/message.cpp.o"

# External object files for target Message
Message_EXTERNAL_OBJECTS =

Message: CMakeFiles/Message.dir/message.cpp.o
Message: CMakeFiles/Message.dir/build.make
Message: CMakeFiles/Message.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Message"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Message.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Message.dir/build: Message
.PHONY : CMakeFiles/Message.dir/build

CMakeFiles/Message.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Message.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Message.dir/clean

CMakeFiles/Message.dir/depend:
	cd /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /export/tmp/4205_34/ele4205_projet_aut2023_34/commun /export/tmp/4205_34/ele4205_projet_aut2023_34/commun /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build /export/tmp/4205_34/ele4205_projet_aut2023_34/commun/build/CMakeFiles/Message.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Message.dir/depend
