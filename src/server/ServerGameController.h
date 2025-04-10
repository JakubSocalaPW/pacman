#ifndef SERVERGAMECONTROLLER_H
#define SERVERGAMECONTROLLER_H

#include "network/NetworkHost.h"
#include "core/LevelGenerator.h"
#include "../common/level/Level.h"
#include <string>

class PlayerCharacter;

/**
 * @class ServerGameController
 * @brief Controls the server-side game logic, managing the game state,
 * player interactions, and network communication.
 *
 * This class is responsible for maintaining the game level, tracking players,
 * handling player input, detecting collisions, updating the game state,
 * and broadcasting updates to all connected clients through the NetworkHost.
 */
class ServerGameController {
private:
    bool _isGameActive = false;
    NetworkHost _networkHost;
    LevelGenerator _levelGenerator;

    void _detectCollisions();
    void _handlePlayerMovement(int playerId, int direction);

public:
    /**
     * @brief Constructor for the ServerGameController class.
     *
     * Initializes the server game controller, potentially setting up the initial
     * game state and the network host.
     */
    ServerGameController();

    /**
     * @brief Broadcasts the updated game state to all connected clients.
     *
     * This method retrieves the current game state (e.g., level, player positions, scores)
     * and uses the NetworkHost to send this information to all active clients.
     */
    void broadcastUpdatedState();

    /**
     * @brief Starts the game, setting the game active flag and initiating the game loop
     * or other necessary processes.
     */
    void startGame();

    /**
     * @brief Gets a reference to the current game level being played.
     * @return A reference to the Level object.
     */
    Level& getCurrentLevel();

    /**
     * @brief Adds a new player to the game based on their provided name.
     * @param name The nickname or identifier of the new player.
     *
     * This method creates a new player entity, associates it with a client,
     * and adds it to the game state.
     */
    void addPlayer(const std::string& name);

    /**
     * @brief Processes a movement command from a player.
     * @param name The nickname of the player who sent the move command.
     * @param direction The requested direction of movement.
     */
    void movePlayer(const std::string& name, int direction);

    /**
     * @brief Removes a player from the game based on their name.
     * @param name The nickname of the player to remove.
     */
    void removePlayer(const std::string& name);
};

#endif //SERVERGAMECONTROLLER_H