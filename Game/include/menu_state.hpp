// Copyright 2015, Aaron Ceross

#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "game_state.hpp"

#define NUM_OPTIONS 3
// Set the values for the game window
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class MenuState : public GameState {
 private:
  sf::View view;
  sf::Text options[NUM_OPTIONS];
  sf::Font font;

  int selection;

  // std::vector<std::string> options = { "Start Game", "Help", "Quit"};

  void loadGame();

 public:
  virtual void draw(const sf::RenderWindow &window);
  virtual void update();
  virtual void handleInput();

  void moveUp();
  void moveDown();

  explicit MenuState(GameStateManager* gsm);
  virtual ~MenuState();
};


#endif  // MENU_STATE_HPP
