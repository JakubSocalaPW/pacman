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
        src/server/ServerController.h
        src/server/network/NetworkHost.cpp
        src/server/network/NetworkHost.h)
target_link_libraries(pacman sfml-system sfml-network)

add_executable(client client.cpp
        src/client/ClientController.cpp
        src/client/ClientController.h
        src/client/core/Player.cpp
        src/client/core/Player.h
        src/client/core/input/KeyboardController.cpp
        src/client/core/input/KeyboardController.h
        src/client/network/NetworkClient.cpp
        src/client/network/NetworkClient.h
        src/client/core/Level.cpp
        src/client/core/Level.h
        src/client/view/Window.cpp
        src/client/view/Window.h
        src/client/core/Pickable.cpp
        src/client/core/Pickable.h)
target_link_libraries(client sfml-system sfml-window sfml-graphics sfml-network)