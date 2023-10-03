cmake_minimum_required(VERSION 3.0)

project(r-type)

cmake_policy(SET CMP0077 NEW)
# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(r-type_engine src/main.cpp)

# Specify the C++ standard
target_compile_features(r-type_engine PRIVATE cxx_std_11)

# Link SFML libraries
target_link_libraries(r-type_engine sfml-graphics sfml-window sfml-system)
