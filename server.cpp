#include <iostream>

#include "src/server/ServerGameController.h"
#include "src/server/core/LevelGenerator.h"
#include "src/server/network/NetworkHost.h"

int main () {

  ServerGameController gameController;
  gameController.startGame();
  std::cout << "Press Enter to stop server..." << std::endl;
  std::cin.get();

  return 0;
}
