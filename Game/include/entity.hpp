// Copyright 2015, Aaron Ceross

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
 public:
  sf::Vector2f GetVelocity_() const;
  void SetVelocity(float vx, float vy);
  void SetVeloctity(sf::Vector2f velocity);

 private:
  sf::Vector2f velocity_;
};

#endif  // ENTITY_HPP
