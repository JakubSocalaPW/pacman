#ifndef NETWORKHOST_H
#define NETWORKHOST_H

#include <atomic>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <SFML/Network.hpp>

#include "../../common/player//Player.h"
#include "../core/LevelGenerator.h"

class ServerGameController;

/**
 * @class NetworkHost
 * @brief Manages the network hosting for the game server.
 *
 * This class is responsible for listening for incoming client connections,
 * accepting new clients, handling communication with connected clients,
 * and broadcasting the game state. It runs on a separate thread to avoid
 * blocking the main server logic.
 */
class NetworkHost {
private:
    sf::TcpListener _listener;
    std::atomic<bool> _running = false;
    int _port;
    std::thread _gameThread;
    std::vector<sf::TcpSocket*> _clients;
    std::map<std::string, sf::TcpSocket*> _playersNames;
    std::mutex _playersMutex;
    ServerGameController* _serverController;
    bool _areLogsinQueue = false;

    void _waitForConnection();
    void _acceptNewClients();
    void _processClientMessages();

public:
    /**
     * @brief Constructor for the NetworkHost class.
     * @param portNumber The port number to listen on for client connections.
     * @param controller A pointer to the ServerGameController instance.
     */
    NetworkHost(int portNumber, ServerGameController* controller);

    /**
     * @brief Broadcasts the current game state (e.g., level layout, player positions) to all connected clients.
     * @param state A constant reference to the Level object representing the current game state.
     */
    void broadcastGameState(const Level& state);

    /**
     * @brief Broadcasts new message as log
     * @param message The message to be broadcasted to all clients.
     */
    void broadcastLogs(std::string message);

    /**
     * @brief Starts the network server, beginning to listen for client connections
     * on the specified port.
     * @return True if the server started successfully, false otherwise.
     */
    bool startServer();

    /**
     * @brief Destructor for the NetworkHost class.
     *
     * Cleans up resources, such as closing client sockets and stopping the server thread.
     */
    ~NetworkHost();
};

#endif //NETWORKHOST_H