// Copyright 2015, Aaron Ceross

#include "../include/collision.hpp"

bool Collision::Collide(sf::Vector2f p, Tile t) {
  if (t.getGlobalBounds().contains(p)) {
    return true;
  }
  return false;
}
