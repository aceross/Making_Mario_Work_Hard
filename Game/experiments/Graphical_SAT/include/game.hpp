// Copyright 2015, Aaron Ceross

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include "../lib/zchaff/SAT.h"
#include "variable_manager.hpp"

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
  void InitialiseTexts();
  void LoadAssets();

  void ReadFile();
  void InitialiseCircles();

  void DisplayClauses();

  void Solve();
  void DisplayResults(SAT_Manager SAT_manager_, int outcome);

  void Decision(SAT_Manager SAT_manager_);

  void Update();
  void Draw();
  void HandleEvents();

  void PrintSolution();

 private:
  SAT_Manager     SAT_manager_;
  VariableManager var_mngr;

  sf::RenderWindow    window_;
  sf::Font            font_;
  sf::ContextSettings settings_;
  sf::Event           event_;

  sf::CircleShape     circle_;

  sf::Text title_text_;
  sf::Text instance_text_;
  sf::Text solution_text_;
  sf::Text result_text_;

 private:
  int satisfiability_result_;
  int num_literals_;
  int num_variables_;
  int num_clauses_;

  std::string assignment_;

  std::vector<sf::CircleShape> objects_;
};

#endif  // GAME_HPP
