
#ifndef CLIENTGAMECONTROLLER_H
#define CLIENTGAMECONTROLLER_H


#include "./core/input/KeyboardController.h"
#include "./network/NetworkClient.h"
#include "core/Scoreboard.h"
#include "SFML/Network/IpAddress.hpp"
#include "view/View.h"

class ClientGameController {
    KeyboardController _keyboard;
    Scoreboard _scoreboard;
    sf::IpAddress _ipAddress;
    NetworkClient _networkClient;
    View _view;
    Level _level;
    void _sendPlayerInput();
    void _getIpFromUser();

    void _runGame();

public:
    ClientGameController();
    void registerGame();
};

#endif //CLIENTGAMECONTROLLER_H
