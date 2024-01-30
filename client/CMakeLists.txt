# CMakeLists.txt for the 'client' directory
cmake_minimum_required(VERSION 3.4)

# Set the project name and version
project(Client VERSION 1.0)

find_package(OpenCV REQUIRED)

# Create an executable for the client application
add_executable(Client client.cpp handlers.cpp ../commun/video.cpp ../commun/TCP.cpp ../commun/message.cpp)

target_link_libraries(Client  ${OpenCV_LIBS})

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
