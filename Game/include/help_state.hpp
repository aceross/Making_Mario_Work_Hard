// Copyright 2015, Aaron Ceross

#ifndef HELP_STATE_HPP
#define HELP_STATE_HPP

#include <iostream>
#include <string>
#include "game_state.hpp"

class HelpState : public GameState {
 public:
  virtual void draw(const sf::RenderWindow &window);
  virtual void update();
  virtual void handleInput();

  explicit HelpState(GameStateManager* gsm);
  virtual ~HelpState();

 private:
  sf::View view;
  sf::Text help_text;
  sf::Font font;
};

#endif  // HELP_STATE_HPP
