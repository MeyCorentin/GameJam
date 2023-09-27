cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(r-type)

add_executable(r-type_client src/main.cpp src/UDPclient.cpp ../server/src/BinaryProtocole.cpp)

if(APPLE)
    find_package(Boost 1.82 REQUIRED COMPONENTS system)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(r-type_client ${Boost_LIBRARIES})
endif()
