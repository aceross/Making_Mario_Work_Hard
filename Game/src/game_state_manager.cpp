// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <stack>

#include "../include/game_state_manager.hpp"
#include "../include/game_state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/animation_handler.hpp"
#include "../include/tile.hpp"

void GameStateManager::loadTiles() {}

void GameStateManager::loadTextures() {}

void GameStateManager::pushState(GameState* state) {
  this->states.push(state);
  return;
}

void GameStateManager::popState() {
  // delete this->states.top();
  this->states.pop();
  return;
}

void GameStateManager::changeState(GameState* state) {
  if (!this->states.empty()) popState();
  pushState(state);
  return;
}

GameState* GameStateManager::peekState() {
  if (this->states.empty()) return nullptr;
  return this->states.top();
}

void GameStateManager::gameLoop() {
  while (this->window.isOpen() && !this->game_over) {
    if (peekState() == nullptr) continue;
    peekState()->handleInput();
    peekState()->update();
    this->window.clear();
    peekState()->draw(this->window);
    this->window.display();
  }
  printf("Quitting game loop...\n");
}

GameStateManager::GameStateManager() {
  this->loadTextures();
  this->loadTiles();

  this->settings.antialiasingLevel = 8;
  this->window.create(sf::VideoMode(800, 600), "Making Mario Work Hard",
                      sf::Style::Default, settings);
  this->window.setFramerateLimit(60);
  // this->background.setTexture(this->texmgr.getRef("background"));
}

GameStateManager::~GameStateManager() {
  while (!this->states.empty()) popState();
}
