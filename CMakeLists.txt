cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(r-type)

add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)
