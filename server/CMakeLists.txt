cmake_minimum_required(VERSION 3.0)

project(r-type)

add_executable(r-type_server src/main.cpp src/UDPserver.cpp)
# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Specify the C++ standard
target_compile_features(r-type_server PRIVATE cxx_std_11)

# Link SFML libraries
target_link_libraries(r-type_server sfml-graphics sfml-window sfml-system)

