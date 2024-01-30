# CMakeLists.txt for the 'commun' directory
cmake_minimum_required(VERSION 3.4)

# Set the project name and version
project(Commun VERSION 1.0)
# Define a library for common code that can be reused in both server and client
#add_library(message message.cpp message.h)
add_executable(Message message.cpp)

# Specify the include directory for message.h
#target_include_directories(message PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)