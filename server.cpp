#include <iostream>

#include "src/server/core/LevelGenerator.h"
#include "src/server/network/NetworkHost.h"

int main () {

  //LevelGenerator lg;
  NetworkHost sc(5555);
  std::cout << sc.startServer() << std::endl;
  std::cout << "Press Enter to stop server..." << std::endl;
  std::cin.get();

  return 0;
}
