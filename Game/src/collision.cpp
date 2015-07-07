// Copyright 2015, Aaron Ceross

#include "../include/collision.hpp"

bool Collision::Collide(Player p, Tile t) {
  printf("Player postion before collison test : x = %f, y = %f\n",
          p.position_.x, p.position_.y);

  // sf::FloatRect tile   = t.getGlobalBounds();
  sf::FloatRect player = p.getGlobalBounds();

  if (player.contains(t.GetTilePosition())) {
    printf("Intersection!!!!!!!!!\n");
    return true;
  }
  return false;
}
