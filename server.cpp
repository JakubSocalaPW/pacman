#include <iostream>

#include "src/server/network/NetworkHost.h"

int main () {

  NetworkHost sc(5555);
  std::cout << sc.startServer() << std::endl;
  std::cout << "Press Enter to stop server..." << std::endl;
  std::cin.get();

  return 0;
}
