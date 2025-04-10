#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <string>
#include <optional>

#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/Packet.hpp"
#include "../../common/level/Level.h"

/**
 * @class NetworkClient
 * @brief A class responsible for handling network communication as a client.
 *
 * This class provides methods to connect to a server, send player information
 * and commands, and receive state updates from the server.
 */
class NetworkClient {
private:
    sf::TcpSocket _socket;

public:
    /**
     * @brief Attempts to connect to a server at the specified IP address and port.
     * @param ip The IP address of the server.
     * @param port The port number of the server.
     * @return True if the connection was successful, false otherwise.
     */
    bool connectToServer(const sf::IpAddress& ip, int port);

    /**
     * @brief Sends the user's name to the connected server.
     * @param name The user's name as a string.
     */
    void sendUserName(const std::string& name);

    /**
     * @brief Attempts to receive a state update packet from the server.
     * @return An optional sf::Packet containing the state update if received
     * successfully
     */
    std::optional<sf::Packet> getStateUpdate();

    /**
     * @brief Sends a move command to the server indicating the player's desired movement direction.
     * @param direction An integer representing the movement direction. 0 - up, 1 - right, 2 - down, 3 - left.
     */
    void sendMoveCommand(int direction);

    /**
     * @brief Disconnects the client from the server and closes the socket.
     */
    void disconnectFromServer();
};

#endif //NETWORKCLIENT_H