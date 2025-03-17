#ifndef NETWORKHOST_H
#define NETWORKHOST_H

#include <atomic>
#include <thread>
#include <SFML/Network.hpp>

class NetworkHost {
    sf::TcpListener listener;
    std::atomic<bool> running = false;
    int port;
    std::thread gameThread;


    public:
    NetworkHost(int port);
    bool startServer();
    void waitForConnection();
    void acceptNewClients();
    void processClientMessages();
};



#endif //NETWORKHOST_H
