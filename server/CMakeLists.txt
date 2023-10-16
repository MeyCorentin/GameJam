# Spécifiez la version minimale de CMake
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nom du projet
project(r-type_server)
# Liste des fichiers source de votre serveur
file(GLOB server_sources "src/main.cpp" "src/UDPserver.cpp" "src/BinaryProtocole.cpp")

# Créez l'exécutable pour le serveur
add_executable(r-type_server ${server_sources})

# Find SFML (si nécessaire)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Specify the C++ standard
target_compile_features(r-type_server PRIVATE cxx_std_11)

target_include_directories(r-type_server PRIVATE includes)

find_library(RTYPE_LIBRARY r-type_library HINTS ../engine/build)

target_link_libraries(r-type_server sfml-graphics sfml-window sfml-system pthread ${RTYPE_LIBRARY})
