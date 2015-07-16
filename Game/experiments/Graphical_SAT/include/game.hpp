// Copyright 2015, Aaron Ceross

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../lib/zchaff/SAT.h"

// Values for the game window
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class Game {
 public:
  Game();
  ~Game();
  void Run();

 private:
  void InitialiseWindow();
  void Draw();
  void LoadAssets();

 private:
  // SAT_Manager sat_mng_;

  sf::RenderWindow window_;
  sf::Font font_;
  sf::ContextSettings settings_;

 private:
  sf::Text welcome_text_;
};

#endif  // GAME_HPP
