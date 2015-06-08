// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/game_state_manager.hpp"

GameStateManager &GameStateManager::get_instance() {
  static GameStateManager instance;
  return instance;
}

GameStateManager::GameStateManager() {}
GameStateManager::~GameStateManager() {}

void GameStateManager::set_text(std::string text) {
  this->text = text;
}

void GameStateManager::draw_text() {
  std::cout << text << std::endl;
}
