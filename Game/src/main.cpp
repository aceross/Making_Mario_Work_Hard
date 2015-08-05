// Copyright 2015, Aaron Ceross

#include <stdexcept>
#include <iostream>

#include "../include/game_state_manager.hpp"

int main() {
  try {
    GameStateManager gsm;

    gsm.Run();
    std::cout << "Exiting program." << std::endl;
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }

  return 0;
}
