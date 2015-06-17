// Copyright 2015, Aaron Ceross

#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "texture_manager.hpp"
#include "tile.hpp"

// Set the values for the game window
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class GameState;

class GameStateManager {
 private:
  void loadTextures();
  void loadTiles();

 public:
  static const int tileSize = 32;
  bool game_over = false;

  std::stack<GameState*> states;

  sf::RenderWindow    window;
  sf::ContextSettings settings;

  TextureManager texmgr;
  sf::Sprite background;

  std::map<std::string, Tile> tileAtlas;

  void pushState(GameState* state);
  void popState();
  void changeState(GameState* state);
  GameState* peekState();

  void gameLoop();

  GameStateManager();
  ~GameStateManager();
};

#endif  // GAME_STATE_MANAGER_HPP
