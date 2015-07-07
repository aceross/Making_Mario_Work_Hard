// Copyright 2015, Aaron Ceross

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "tile.hpp"
#include "player.hpp"

class Collision {
 public:
  static bool Collide(sf::Vector2f p, Tile t);
};

#endif  // COLLISION_HPP
