// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/entity.hpp"

Entity::Entity()
: movement_()
, hit_points_()
{}

int Entity::GetHitPoints() const {
  return hit_points_;
}

void Entity::Damage(int points) {
  assert(points > 0);
  hit_points_ -= points;
}

void Entity::Destroy() {
  hit_points_ = 0;
}

void Entity::MoveMario(float move_x, float move_y) {
  movement_.x += move_x;
  movement_.y += move_y;
}

void Entity::MoveMario(sf::Vector2f movement) {
  movement_ += movement;
}

void Entity::Remove() {
  Destroy();
}

bool Entity::IsDestroyed() const {
  return hit_points_ <= 0;
}

void Entity::UpdateCurrent(sf::Time delta_time, CommandQueue &commands) {
  move(movement_);
}
