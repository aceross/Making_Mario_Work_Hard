// Copyright 2015, Aaron Ceross

#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "game_state.hpp"

class MenuState : public GameState {
 private:
  sf::View view;
  sf::Text text;
  sf::Font font;

  std::vector<std::string> options = { "Start Game", "Help", "Quit"};

  void loadGame();

 public:
  virtual void draw(const sf::RenderWindow &window);
  virtual void update(const float dt);
  virtual void handleInput();

  explicit MenuState(GameStateManager* gsm);
  virtual ~MenuState();
};


#endif  // MENU_STATE_HPP
