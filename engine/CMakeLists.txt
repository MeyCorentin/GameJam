cmake_minimum_required(VERSION 3.0)

project(r-type)

cmake_policy(SET CMP0077 NEW)


file(GLOB system_sources "src/system/*.cpp")
file(GLOB scene_sources "src/scene/*.cpp")
file(GLOB parser_sources "src/parser/*.cpp")
file(GLOB entity_sources "src/entity/*.cpp")
# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(r-type_engine src/main.cpp src/Ecs.cpp
                ${system_sources}
                ${scene_sources}
                ${parser_sources}
                ${entity_sources})

# Specify the C++ standard
target_compile_features(r-type_engine PRIVATE cxx_std_11)

# Link SFML libraries
target_link_libraries(r-type_engine sfml-graphics sfml-window sfml-system)

include_directories(includes)
