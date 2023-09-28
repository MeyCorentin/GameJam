cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(r-type)

add_executable(r-type_server src/main.cpp src/UDPserver.cpp src/BinaryProtocole.cpp)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(r-type_server ${Boost_LIBRARIES} pthread)
