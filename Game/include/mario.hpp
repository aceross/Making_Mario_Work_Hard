// Copyright 2015, Aaron Ceross

#ifndef MARIO_HPP
#define MARIO_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "entity.hpp"
#include "command.hpp"
#include "resource_identifiers.hpp"
#include "animation.hpp"
#include "text_node.hpp"
#include "tile_map.hpp"

class Mario : public Entity {
 public:
  enum Type { SmallMario, SuperMario, Koopa, Shell, Brick, TypeCount };

 public:
  Mario(Type type, const TextureHolder& textures, const FontHolder& fonts);

  virtual unsigned int  GetCategory() const;
  virtual sf::FloatRect GetBoundingRect() const;
  float GetSpeed() const;

  sf::Vector2f GetLocation();
  void UpdateLocation(int x, int y);
  void UpdateLocation(sf::Vector2f location_update);
  void MoveMario(sf::Vector2f location_update);

 private:
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);

  void UpdateAnimation();
  void HandleCollision();

  void SetWalkCycles();

 private:
  Type         type_;
  sf::Sprite   sprite_;
  sf::Vector2f location_;
  sf::Vector2f previous_location_;
  bool waiting_;
  int move_count_;
  sf::IntRect left_face_mario_;

  std::vector<sf::IntRect> walk_left_;
  std::vector<sf::IntRect> walk_right_;

  bool moving_right_  = false;
  bool moving_left_   = false;
  bool jumping_       = false;
};

#endif  // MARIO_HPP
