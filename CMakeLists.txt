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
        src/common/level/Level.cpp
        src/common/level/Level.h
        src/common/level/PowerUp.cpp
        src/common/level/PowerUp.h
        src/common/abstract/PlayerCharacter.cpp
        src/common/abstract/PlayerCharacter.h
        src/server/core/LevelGenerator.cpp
        src/server/core/LevelGenerator.h
        src/common/level/Objective.cpp
        src/common/level/Objective.h
        src/common/level/Wall.cpp
        src/common/level/Wall.h
        src/common/player/PacMan.cpp
        src/common/player/PacMan.h
        src/common/player/Ghost.cpp
        src/common/player/Ghost.h
        src/common/player/Player.cpp
        src/common/player/Player.h
        src/common/abstract/Drawable.cpp
        src/common/abstract/Drawable.h
        src/server/ServerGameController.h)
target_link_libraries(pacman sfml-system sfml-network)

add_executable(client client.cpp
        src/common/player/Player.cpp
        src/common/player/Player.h
        src/client/core/input/KeyboardController.cpp
        src/client/core/input/KeyboardController.h
        src/client/network/NetworkClient.cpp
        src/client/network/NetworkClient.h
        src/common/level/Level.cpp
        src/common/level/Level.h
        src/client/view/Window.cpp
        src/client/view/Window.h
        src/common/abstract/PlayerCharacter.cpp
        src/common/abstract/PlayerCharacter.h
        src/common/player/PacMan.cpp
        src/common/player/PacMan.h
        src/common/player/Ghost.cpp
        src/common/player/Ghost.h
        src/common/level/PowerUp.cpp
        src/common/level/PowerUp.h
        src/common/level/Objective.cpp
        src/common/level/Objective.h
        src/server/core/LevelGenerator.cpp
        src/server/core/LevelGenerator.h
        src/client/ClientGameController.cpp
        src/client/ClientGameController.h
        src/common/abstract/Drawable.cpp
        src/common/abstract/Drawable.h
        src/common/abstract/Pickable.cpp
        src/common/abstract/Pickable.h
        src/client/view/View.cpp
        src/client/view/View.h
        src/client/core/Scoreboard.cpp
        src/client/core/Scoreboard.h
        src/common/level/Wall.cpp
        src/common/level/Wall.h)
target_link_libraries(client sfml-system sfml-window sfml-graphics sfml-network)


set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES TRUE)

#if (MINGW)
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -static-libwinpthread")
#endif()