cmake_minimum_required(VERSION 3.0)

project(r-type)

cmake_policy(SET CMP0077 NEW)

add_executable(r-type_client src/main.cpp src/UDPclient.cpp)
# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Specify the C++ standard
target_compile_features(r-type_client PRIVATE cxx_std_11)

# Link SFML libraries
target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system)