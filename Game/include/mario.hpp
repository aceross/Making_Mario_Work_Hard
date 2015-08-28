// Copyright 2015, Aaron Ceross

#ifndef MARIO_HPP
#define MARIO_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "entity.hpp"
#include "navigation_manager.hpp"
#include "command.hpp"
#include "resource_identifiers.hpp"
#include "animation.hpp"
#include "text_node.hpp"
#include "tile_map.hpp"

class Mario : public Entity {
 public:
  enum Type { SmallMario, SuperMario, TypeCount };

 public:
  Mario(Type type, const TextureHolder& textures, const FontHolder& fonts);

  virtual unsigned int  GetCategory() const;
  virtual sf::FloatRect GetBoundingRect() const;
  float GetSpeed() const;

  sf::Vector2f GetLocation();
  void UpdateLocation(int x, int y);
  void UpdateLocation(sf::Vector2f location_update);
  // void MoveMario(sf::Vector2f location_update);

  // sf::Sprite   sprite_;

  void InitialiseLevelNavigator(TileMap tm);

  NavigationManager navigator_;

 private:
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);

  // void UpdateMovementPattern(sf::Time delta_time);
  // void UpdateTexts();
  void UpdateAnimation();

 private:
  Type         type_;
  sf::Sprite   sprite_;
  sf::Vector2f location_;
  bool waiting_;

  // int clauses_true_;
  // int clauses_false_;

  // bool moving_right_  = false;
  // bool moving_left_   = false;
  // bool jumping_       = false;
  // bool falling_       = false;
  // bool top_collision_ = false;
  // bool can_move_      = false;

};

#endif  // MARIO_HPP
