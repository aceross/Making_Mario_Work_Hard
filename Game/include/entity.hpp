// Copyright 2015, Aaron Ceross

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "scene_node.hpp"
#include "command_queue.hpp"

class Entity : public SceneNode {
 public:
  Entity();
  sf::Vector2f GetVelocity() const;
  void SetVelocity(float vx, float vy);
  void SetVeloctity(sf::Vector2f velocity);

 private:
  sf::Vector2f velocity_;

 protected:
  using SceneNode::UpdateCurrent;
  // virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);
};

#endif  // ENTITY_HPP
