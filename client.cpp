#include <iostream>

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include "src/client/ClientGameController.h"
#include "src/client/view/Window.h"
#include "src/common/level//Level.h"
#include "src/client/core/input/KeyboardController.h"

int main () {
    std::cout << "Starting game client.\n";

    ClientGameController clientGameController;
    clientGameController.registerGame();

    return 0;
}
