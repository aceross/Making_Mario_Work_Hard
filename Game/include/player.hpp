// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
 public:
  Player();
  ~Player();
  void draw(const sf::RenderWindow &window);

  sf::Sprite  sprite;

 private:
  sf::Texture texture;
};

#endif  // PLAYER_HPP
