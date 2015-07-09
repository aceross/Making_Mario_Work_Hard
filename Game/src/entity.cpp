// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/entity.hpp"

void Entity::SetVeloctity(sf::Vector2f velocity) {
  velocity_ = velocity;
}

void Entity::SetVelocity(float vx, float vy) {
  velocity_.x = vx;
  velocity_.y = vy;
}

sf::Vector2f Entity::GetVelocity_() const {
  return velocity_;
}
