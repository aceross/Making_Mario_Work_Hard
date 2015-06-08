// Copyright 2015, Aaron Ceross

#include <string>
#include "headers/game_state_manager.hpp"

GameState *current_state, *new_state;

GameStateManager &GameStateManager::GetInstance() {
  static GameStateManager instance;
  return instance;
}

GameStateManager::GameStateManager()  {}
GameStateManager::~GameStateManager() {}

void GameStateManager::Initialise() {
  current_state = new SplashScreen();
}

void GameStateManager::LoadContent() {
  current_state->LoadContent();
}

void GameStateManager::Update() {
  current_state->Update();
}

void GameStateManager::Draw(sf::RenderWindow &Window) {
  current_state->Draw(Window);
}
