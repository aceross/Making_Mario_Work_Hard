// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.hpp"
#include "entity_manager.hpp"
#include "map.hpp"

class Player {
 public:
  Player();
  // Player(sf::RenderWindow* window, EntityManager* e_mgr, Map* map,
  //                                                         float x, float y);
  ~Player();
  void draw(const sf::RenderWindow &window);
  void Collision(Entity* entity);
  sf::Sprite  sprite;
  sf::Texture texture;

 private:
  EntityManager* e_mgr;
};

#endif  // PLAYER_HPP
