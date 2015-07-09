// Copyright 2015, Aaron Ceross

#include <stdexcept>
#include <iostream>

#include "../include/game_state_manager.hpp"
#include "../include/menu_state.hpp"

int main() {
  try {
    GameStateManager gsm;

    gsm.pushState(new MenuState(&gsm));
    gsm.gameLoop();
    printf("Exiting program.\n");
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }


  return 0;
}
