#include "ClientGameController.h"
#include <iostream>
#include "SFML/Network/IpAddress.hpp"

ClientGameController::ClientGameController(): _ipAddress(127, 0, 0 ,1) { }


void ClientGameController::registerGame() {
    const int DEFAULT_PORT = 5555;
    _getIpFromUser();
    _networkClient.connectToServer(_ipAddress, DEFAULT_PORT);
    std::string name;
    std::cin >> name;
    _networkClient.sendUserName(name);
    _runGame();
}

void ClientGameController::_getIpFromUser() {
    std::optional<sf::IpAddress> optionalAddress;
    do {
        std::string ipFromUser;
        std::cout << "Enter an IP address or hostname: ";
        std::cin >> ipFromUser;

        optionalAddress = sf::IpAddress::resolve(ipFromUser);
    } while (!optionalAddress);

    _ipAddress = *optionalAddress;
    std::cout << "Thank you! Received valid IP Address: " << _ipAddress.toString() << std::endl;
}

void ClientGameController::_runGame() {
    sf::Clock clock;

    bool isGameStillOn = true;
    while (isGameStillOn) {
        isGameStillOn = _view.refreshWindow();

        if (clock.getElapsedTime().asSeconds() >= 0.05f) {
            _view.drawLevel(_level, _scoreboard);
            _sendPlayerInput();
            clock.restart();
        }

        if (auto newState= _networkClient.getStateUpdate()) {
            _scoreboard.clearPlayers();
            if (newState) {
               *newState >> _level;
            }

            for (auto player: _level.getPlayerCharacters()) {
                _scoreboard.addPlayer(&player->getPlayer());
            }
        }
    }
}

void ClientGameController::_sendPlayerInput() {
    if (_view.hasFocus()) {
        if (_keyboard.isArrowDownPressed()) {
            _networkClient.sendMoveCommand(2); //todo move direction to enum
        }
        else if (_keyboard.isArrowUpPressed()) {
            _networkClient.sendMoveCommand(0);
        }
        else if (_keyboard.isArrowLeftPressed()) {
            _networkClient.sendMoveCommand(3);

        }
        else if (_keyboard.isArrowRightPressed()) {
            _networkClient.sendMoveCommand(1);
        }
    }
}