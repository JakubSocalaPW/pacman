cmake_minimum_required(VERSION 3.30)
project(pacman)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git

        GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

add_executable(pacman server.cpp
        src/server/ServerController.cpp
        src/server/ServerController.h)
target_link_libraries(pacman sfml-system sfml-network)

add_executable(client client.cpp
        src/client/ClientController.cpp
        src/client/ClientController.h)
target_link_libraries(client sfml-system sfml-window sfml-graphics sfml-network)