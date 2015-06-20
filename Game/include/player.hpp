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
  sf::Texture texture;

 private:
};

#endif  // PLAYER_HPP
