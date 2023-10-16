# Spécifiez la version minimale de CMake
cmake_minimum_required(VERSION 3.0)

# Nom du projet
project(r-type)

# Mettez à jour la version C++ utilisée par CMake à C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Liste des fichiers source de la bibliothèque
file(GLOB library_sources "src/system/*.cpp" "src/scene/*.cpp" "src/parser/*.cpp" "src/entity/*.cpp" "src/*.cpp")

# Créez une bibliothèque (shared library) à partir des sources
add_library(r-type_library SHARED ${library_sources})

# Incluez les répertoires d'en-têtes pour la bibliothèque
target_include_directories(r-type_library PRIVATE includes)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Since SFML provides imported targets, we can link against them directly
# Linking this way also ensures that we get the proper include directories and dependencies
target_link_libraries(r-type_library sfml-graphics sfml-window sfml-system)

# Créez un exécutable à partir du fichier source principal
add_executable(r-type_engine src/main.cpp src/Ecs.cpp)

# Liez l'exécutable avec la bibliothèque
target_link_libraries(r-type_engine r-type_library)

# Incluez les répertoires d'en-têtes pour l'exécutable
target_include_directories(r-type_engine PRIVATE includes)
