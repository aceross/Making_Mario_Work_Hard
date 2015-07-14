// Copyright 2015, Aaron Ceross

#include <stdexcept>
#include <iostream>

#include "../include/game_state_manager.hpp"

int main() {
  try {
    GameStateManager gsm;

    gsm.Run();
    printf("Exiting program.\n");
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }


  return 0;
}
