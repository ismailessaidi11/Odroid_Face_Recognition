# CMakeLists.txt for the 'serveur' directory
cmake_minimum_required(VERSION 3.4)

# Set the project name and version
project(Server VERSION 1.0)

find_package(OpenCV REQUIRED)

# Create an executable for the server application
add_executable(Server server.cpp odroid.cpp serverHandlers.cpp ../commun/video.cpp ../commun/TCP.cpp ../commun/message.cpp)

target_link_libraries(Server  ${OpenCV_LIBS})
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
