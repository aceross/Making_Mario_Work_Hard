// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <stack>

#include "../include/game_state_manager.hpp"
#include "../include/game_state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/animation_handler.hpp"
#include "../include/tile.hpp"

void GameStateManager::loadTiles() {
  // Animation staticAnim(0, 0, 1.0f);
  // this->tileAtlas["grass"] =
  //     Tile(this->tileSize, 1, texmgr.getRef("grass"),
  //         { staticAnim },
  //         TileType::GRASS, 50, 0, 1);
  // tileAtlas["forest"] =
  //     Tile(this->tileSize, 1, texmgr.getRef("forest"),
  //         { staticAnim },
  //         TileType::FOREST, 100, 0, 1);
  // tileAtlas["water"] =
  //     Tile(this->tileSize, 1, texmgr.getRef("water"),
  //         { Animation(0, 3, 0.5f),
  //         Animation(0, 3, 0.5f),
  //         Animation(0, 3, 0.5f) },
  //         TileType::WATER, 0, 0, 1);
  // tileAtlas["residential"] =
  //     Tile(this->tileSize, 2, texmgr.getRef("residential"),
  //         { staticAnim, staticAnim, staticAnim,
  //         staticAnim, staticAnim, staticAnim },
  //         TileType::RESIDENTIAL, 300, 50, 6);
  // tileAtlas["commercial"] =
  //     Tile(this->tileSize, 2, texmgr.getRef("commercial"),
  //         { staticAnim, staticAnim, staticAnim, staticAnim},
  //         TileType::COMMERCIAL, 300, 50, 4);
  // tileAtlas["industrial"] =
  //     Tile(this->tileSize, 2, texmgr.getRef("industrial"),
  //         { staticAnim, staticAnim, staticAnim,
  //         staticAnim },
  //         TileType::INDUSTRIAL, 300, 50, 4);
  // tileAtlas["road"] =
  //     Tile(this->tileSize, 1, texmgr.getRef("road"),
  //         { staticAnim, staticAnim, staticAnim,
  //         staticAnim, staticAnim, staticAnim,
  //         staticAnim, staticAnim, staticAnim,
  //         staticAnim, staticAnim },
  //         TileType::ROAD, 100, 0, 1);

  return;
}

void GameStateManager::loadTextures() {
  // texmgr.loadTexture("grass",         "media/grass.png");
  // texmgr.loadTexture("forest",        "media/forest.png");
  // texmgr.loadTexture("water",         "media/water.png");
  // texmgr.loadTexture("residential",   "media/residential.png");
  // texmgr.loadTexture("commercial",    "media/commercial.png");
  // texmgr.loadTexture("industrial",    "media/industrial.png");
  // texmgr.loadTexture("road",          "media/road.png");
  //
  // texmgr.loadTexture("background",    "media/background.png");
}

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
    this->window.clear(sf::Color::Black);
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
