// Copyright 2015, Aaron Ceross

#ifndef DATA_TABLES_HPP
#define DATA_TABLES_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

#include "resource_identifiers.hpp"

class Player;

struct Direction {
  Direction(float angle, float distance)
  : angle_(angle)
  , distance_(distance)
  {}

  float angle_;
  float distance_;
};

struct PlayerData {
  float speed;
  Textures::ID texture;
  sf::IntRect texture_rect;
  sf::Time projectile_interval;
  std::vector<Direction> directions;
  bool has_animation_;
};

std::vector<PlayerData> InitialisePlayerData();

#endif  // DATA_TABLES_HPP
