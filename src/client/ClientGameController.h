
#ifndef CLIENTGAMECONTROLLER_H
#define CLIENTGAMECONTROLLER_H


#include "./core/input/KeyboardController.h"
#include "./network/NetworkClient.h"
#include "SFML/Network/IpAddress.hpp"
#include "view/View.h"

class ClientGameController {
    KeyboardController _keyboard;
    sf::IpAddress _ipAddress;
    NetworkClient _networkClient;
    View _view;
    Level _level;

    void _runGame();

public:
    ClientGameController();
    void registerGame();
    void getIpFromUser();
    void updateGameState();
    void sendPlayerInput();
    void processServerUpdate();
};

#endif //CLIENTGAMECONTROLLER_H
