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
        src/server/network/NetworkHost.cpp
        src/server/network/NetworkHost.h
        src/server/ServerGameController.cpp
        src/client/core/Level.cpp
        src/client/core/Level.h
        src/client/core/PowerUp.cpp
        src/client/core/PowerUp.h
        src/server/core/LevelGenerator.cpp
        src/server/core/LevelGenerator.h
        src/client/core/Objective.cpp
        src/client/core/Objective.h
        src/client/core/Wall.cpp
        src/client/core/Wall.h
        src/client/core/Player.cpp
        src/client/core/Player.h
        src/client/core/abstract/Drawable.cpp
        src/client/core/abstract/Drawable.h
        src/server/ServerGameController.h)
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
        src/client/core/Pickable.h
        src/client/core/PlayerCharacter.cpp
        src/client/core/PlayerCharacter.h
        src/client/core/PacMan.cpp
        src/client/core/PacMan.h
        src/client/core/Ghost.cpp
        src/client/core/Ghost.h
        src/client/core/PowerUp.cpp
        src/client/core/PowerUp.h
        src/client/core/Objective.cpp
        src/client/core/Objective.h
        src/server/core/LevelGenerator.cpp
        src/server/core/LevelGenerator.h
        src/client/ClientGameController.cpp
        src/client/ClientGameController.h
        src/client/core/abstract/Drawable.cpp
        src/client/core/abstract/Drawable.h
        src/client/core/abstract/Pickable.cpp
        src/client/core/abstract/Pickable.h
        src/client/view/View.cpp
        src/client/view/View.h
        src/client/core/Scoreboard.cpp
        src/client/core/Scoreboard.h
        src/client/core/Wall.cpp
        src/client/core/Wall.h)
target_link_libraries(client sfml-system sfml-window sfml-graphics sfml-network)