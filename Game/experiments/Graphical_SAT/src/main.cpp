// Copyright 2015, Aaron Ceross

#include <iostream>
#include "../include/game.hpp"

int main(int argc, char* argv[]) {
  try {
    Game game;

    game.Run();
    std::cout << "...Exiting program..." << std::endl;
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }

  return 0;
}
