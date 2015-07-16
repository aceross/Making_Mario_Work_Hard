// Copyright 2015, Aaron Ceross

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "../lib/zchaff/SAT.h"

// Values for the game window
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Values for parsing file
#define MAX_LINE_LENGTH 65536
#define MAX_WORD_LENGTH 64

class Game {
 public:
  Game();
  ~Game();
  void Run();

 private:
  void InitialiseWindow();
  void LoadAssets();

  void ReadFile();

  void Draw();
  void HandleEvents();

 private:
  SAT_Manager SAT_manager_;

  sf::RenderWindow window_;
  sf::Font font_;
  sf::ContextSettings settings_;
  sf::Event event_;

 private:
  sf::Text welcome_text_;
};

#endif  // GAME_HPP
