// Copyright 2015, Aaron Ceross

#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#define MAX 100

class Maze {
 private:
  char layout[MAX][MAX];
  int height, width;
  void ReadFile();
  void Print();
 public:
  Maze();
  ~Maze();
  void Run();
};

#endif  // MAZE_HPP
