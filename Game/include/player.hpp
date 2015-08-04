// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "entity.hpp"
#include "command.hpp"
#include "resource_identifiers.hpp"
#include "animation.hpp"
#include "text_node.hpp"

class Player : public Entity {
 public:
  enum Type { SmallPlayer, SuperMario, TypeCount };

 public:
  Player(Type type, const TextureHolder& textures, const FontHolder& fonts);

  virtual sf::FloatRect GetBoundingRect() const;
  // virtual void          Remove();
  // float                 GetMaxSpeed() const;

  sf::Vector2i GetLocation();
  void UpdateLocation(int x, int y);
  void UpdateLocation(sf::Vector2i location_update);

 private:
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);

  // void UpdateMovementPattern(sf::Time delta_time);
  // void UpdateTexts();
  void UpdateAnimation();

 private:
  Type         type_;
  sf::Sprite   sprite_;
  sf::Vector2i location_;
  // Command      fire_command_;
  // std::size_t  direction_index_;
  //
  // int clauses_true_;
  // int clauses_false_;

  // bool moving_right_  = false;
  // bool moving_left_   = false;
  // bool jumping_       = false;
  // bool falling_       = false;
  // bool top_collision_ = false;
  // bool can_move_      = false;

};

#endif  // PLAYER_HPP
