// Copyright 2015, Aaron Ceross

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game_state_manager.hpp"

class GameState {
 public:
  virtual ~GameState() {}

  virtual void draw(const sf::RenderWindow &window) = 0;
  virtual void update()                             = 0;
  virtual void handleInput()                        = 0;

 protected:
  GameStateManager* gsm;
  sf::RenderWindow* window;
};

#endif  // GAME_STATE_HPP
