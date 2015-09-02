// Copyright 2015, Aaron Ceross

#include <vector>

#include "../include/data_table.hpp"
#include "../include/mario.hpp"
#include "../include/world_object.hpp"

using namespace std::placeholders;

std::vector<PlayerData> InitialisePlayerData() {
  std::vector<PlayerData> data(Mario::TypeCount);

  data[Mario::SmallMario].speed          = 2.5f;
  data[Mario::SmallMario].hit_points_    = 1;
  data[Mario::SmallMario].texture        = Textures::Mario;
  data[Mario::SmallMario].texture_rect   = sf::IntRect(176, 32, 16, 16);
  data[Mario::SmallMario].has_animation_ = true;

  data[Mario::SuperMario].speed          = 2.5f;
  data[Mario::SuperMario].hit_points_    = 1;
  data[Mario::SuperMario].texture        = Textures::Mario;
  data[Mario::SuperMario].texture_rect   = sf::IntRect(176, 0, 16, 32);
  data[Mario::SuperMario].has_animation_ = true;

  data[Mario::Koopa].speed          = 2.5f;
  data[Mario::Koopa].hit_points_    = 1;
  data[Mario::Koopa].texture        = Textures::Koopa;
  data[Mario::Koopa].texture_rect   = sf::IntRect(206, 30, 24, 24);
  data[Mario::Koopa].has_animation_ = false;

  data[Mario::Shell].speed          = 2.5f;
  data[Mario::Shell].hit_points_    = 1;
  data[Mario::Shell].texture        = Textures::Koopa;
  data[Mario::Shell].texture_rect   = sf::IntRect(330, 34, 16, 16);
  data[Mario::Shell].has_animation_ = false;

  data[Mario::Brick].speed          = 2.5f;
  data[Mario::Brick].hit_points_    = 1;
  data[Mario::Brick].texture        = Textures::World;
  data[Mario::Brick].texture_rect   = sf::IntRect(176, 32, 16, 16);
  data[Mario::Brick].has_animation_ = false;

  return data;
}
