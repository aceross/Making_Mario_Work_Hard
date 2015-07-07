// Copyright 2015, Aaron Ceross

#include "../include/collision.hpp"

bool Collision::Collide(Player p, Tile t) {
  printf("Player postion x = %f, y = %f\n", p.position_.x, p.position_.y);

  sf::FloatRect tile   = t.getGlobalBounds();
  sf::FloatRect player = p.getGlobalBounds();

  printf("Tile values\n");
  printf("Tile ID = %d\n", t.GetTileID());
  printf("Tile Value = %d\n", t.GetTileValue());
  printf("Tile Position x = %f , y = %f\n", t.getPosition().x,
                                            t.getPosition().y);

  if (player.intersects(tile)) {
    printf("Intersection!!!!!!!!!\n");
    return true;
  }
  printf("No Collision\n");
  return false;
}
