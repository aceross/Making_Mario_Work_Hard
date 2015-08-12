// Copyright 2015, Aaron Ceross

#include "../include/shape.hpp"

Shape::Shape(float radius, unsigned int point_count) {
  sf::CircleShape(radius, point_count);
}
