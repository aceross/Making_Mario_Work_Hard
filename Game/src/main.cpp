/*------------------------------------------------------------------------------
    Copyright 2015, Aaron Ceross

    Source code submitted for the MSc Thesis, as part of the
    completion of the MSc in Computer Science at the University of Bristol
------------------------------------------------------------------------------*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game_state_manager.hpp"

int main() {
  GameStateManager::get_instance().set_text("some test");
  GameStateManager::get_instance().draw_text();
  std::cin.get();
  return 0;
}
