cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nom du projet
project(r-type_client)
# Liste des fichiers source de votre serveur
add_executable(r-type_client src/main.cpp src/UDPclient.cpp ../server/src/BinaryProtocole.cpp)

# Find SFML (si nécessaire)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

# Specify the C++ standard
target_compile_features(r-type_client PRIVATE cxx_std_11)

target_include_directories(r-type_client PRIVATE includes)
target_include_directories(r-type_client PUBLIC ${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${nlohmann_json_INCLUDE_DIRS})

find_library(RTYPE_LIBRARY r-type_library HINTS ../engine/build)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system pthread nlohmann_json::nlohmann_json ${RTYPE_LIBRARY})
