// Copyright 2015, Aaron Ceross

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

class Level {
 public:
  Level();
  ~Level();
  unsigned int height;
  unsigned int width;
};

#endif  // level_HPP
