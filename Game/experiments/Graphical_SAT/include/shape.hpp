// Copyright 2015, Aaron Ceross

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Shape : public sf::CircleShape {
 public:
  Shape(float radius, unsigned int point_count);

  // variables
  int variable_value_;
  int literal_value_;

  sf::Color colour;

  std::vector<int> clause_locations_;
};

#endif  // SHAPE_HPP
