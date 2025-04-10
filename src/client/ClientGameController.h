#ifndef CLIENTGAMECONTROLLER_H
#define CLIENTGAMECONTROLLER_H

#include "./core/input/KeyboardController.h"
#include "./network/NetworkClient.h"
#include "core/Scoreboard.h"
#include "SFML/Network/IpAddress.hpp"
#include "view/View.h"

/**
 * @class ClientGameController
 * @brief Controls the client-side game logic, handling input, network communication,
 * and updating the game view.
 *
 * This class manages the main game loop for the client, including processing user
 * input, sending commands to the server via the network client, receiving game
 * state updates, updating the local game state (level and scoreboard), and rendering
 * the game through the view.
 */
class ClientGameController {
private:
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
    /**
     * @brief Constructor for the ClientGameController class.
     *
     * Initializes the client game controller, potentially performing setup tasks
     * such as getting the server IP address.
     */
    ClientGameController();

    /**
     * @brief Starts the game registration process for the client.
     *
     * This function initiates the process of connecting to the server and starting
     * the game loop.
     */
    void registerGame();
};

#endif //CLIENTGAMECONTROLLER_H