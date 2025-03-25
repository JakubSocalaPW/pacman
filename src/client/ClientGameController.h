
#ifndef CLIENTGAMECONTROLLER_H
#define CLIENTGAMECONTROLLER_H


#include "./core/PacMan.h"
#include "./core/input/KeyboardController.h"
#include "./network/NetworkClient.h"

class ClientGameController {
    PacMan m_pacman;
    KeyboardController m_keyboard;
    NetworkClient m_networkClient;

public:
    void registerGame();
    void updateGameState();
    void sendPlayerInput();
    void processServerUpdate();
};

#endif //CLIENTGAMECONTROLLER_H
