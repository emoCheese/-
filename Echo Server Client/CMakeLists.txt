cmake_minimum_required(VERSION 3.22.1)

project(TEST)


set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(Server Server.cpp src/server.cpp)
add_executable(Client Client.cpp src/client.cpp)


