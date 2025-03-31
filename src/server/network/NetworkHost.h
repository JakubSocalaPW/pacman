#ifndef NETWORKHOST_H
#define NETWORKHOST_H

#include <atomic>
#include <thread>
#include <SFML/Network.hpp>

#include "../../client/core/Player.h"
#include "../core/LevelGenerator.h"

class ServerGameController;

class NetworkHost {
    sf::TcpListener listener;
    std::atomic<bool> running = false;
    int port;
    std::thread gameThread;
    std::vector<sf::TcpSocket*> clients;
    std::map<std::string, sf::TcpSocket*> playersNames;
    std::mutex playersMutex;
    ServerGameController* serverController;

    void waitForConnection();
    void acceptNewClients();
    void processClientMessages();

public:
    void broadcastGameState(const Level& state);

    NetworkHost(int port, ServerGameController* serverController);

    bool startServer();


    ~NetworkHost() {
        // Stop the server thread if running
        running = false;
        if (gameThread.joinable()) {
            gameThread.join();
        }

        // Clean up all client sockets
        for (auto& client : clients) {
            delete client;
        }
        clients.clear();
    }
};



#endif //NETWORKHOST_H
