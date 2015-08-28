// Copyright 2015, Aaron Ceross

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "scene_node.hpp"
#include "command_queue.hpp"

class Entity : public SceneNode {
 public:
  Entity();
  int GetHitPoints() const;
  void Damage(int points);
  void Destroy();
  void MoveMario(sf::Vector2f movement);
  void MoveMario(float move_x, float move_y);
  virtual void Remove();
  virtual bool IsDestroyed() const;

 protected:
  // using SceneNode::UpdateCurrent;
  virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);
private:
  sf::Vector2f movement_;
  int hit_points_;
};

#endif  // ENTITY_HPP
