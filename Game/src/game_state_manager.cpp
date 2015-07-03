// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>

#include <stack>

#include "../include/game_state_manager.hpp"
#include "../include/game_state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/animation_handler.hpp"
#include "../include/tile.hpp"

void GameStateManager::loadTiles() {}

void GameStateManager::loadTextures() {}

void GameStateManager::pushState(GameState* state) {
  states.push(state);
  return;
}

void GameStateManager::popState() {
  // delete this->states.top();
  states.pop();
  return;
}

void GameStateManager::changeState(GameState* state) {
  if (!states.empty()) popState();
  pushState(state);
  return;
}

GameState* GameStateManager::peekState() {
  if (states.empty()) return nullptr;
  return states.top();
}

void GameStateManager::gameLoop() {
  while (window.isOpen() && !game_over) {
    if (peekState() == nullptr) continue;

    // Determine the time that passed
    sf::Time delta = updateClock.restart();
    updateTime += delta;  // add up previous leftover time

    // determine the number of iterations to do (100 fps; capped at 10)
    // int loops = std::min<int>(static_cast<int>(updateTime /
    //                                            sf::milliseconds(10)), 10);
    // while (loops--)
    //   // updateSingleStep();                 // update by one fixed timestep
    //   updateTime %= sf::milliseconds(10);    // drop leftover frames
    //   // updateDeltaTime(delta);              // update based on time passed

    peekState()->handleInput();
    peekState()->update();

    window.clear();
    peekState()->draw(window);

    window.display();
    sf::sleep(sf::microseconds(1));
  }
  printf("Quitting game loop...\n");
}

GameStateManager::GameStateManager() {
  loadTextures();
  loadTiles();

  settings.antialiasingLevel = 8;
  window.create(sf::VideoMode(800, 600), "Making Mario Work Hard",
                                          sf::Style::Default, settings);
  window.setFramerateLimit(60);
  // this->background.setTexture(this->texmgr.getRef("background"));
}

GameStateManager::~GameStateManager() {
  while (!states.empty()) popState();
}
