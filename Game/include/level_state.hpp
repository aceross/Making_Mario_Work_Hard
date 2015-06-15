// Copyright 2015, Aaron Ceross

#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "game_state.hpp"

class LevelState : public GameState {
 private:
  sf::View view;
  sf::Text level_text;
  sf::Font font;

 public:
  virtual void draw(const sf::RenderWindow &window);
  virtual void update();
  virtual void handleInput();

  explicit LevelState(GameStateManager* gsm);
  virtual ~LevelState();
};

#endif  // LEVEL_STATE_HPP
