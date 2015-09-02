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

  // data[World::Wall].speed                = 2.5f;
  // data[World::SmallMario].hit_points_    = 1;
  // data[World::SmallMario].texture        = Textures::Mario;
  // data[World::SmallMario].texture_rect   = sf::IntRect(176, 32, 16, 16);
  // data[World::SmallMario].has_animation_ = false;
  //
  // data[World::SuperMario].speed          = 2.5f;
  // data[World::SuperMario].hit_points_    = 1;
  // data[World::SuperMario].texture        = Textures::Mario;
  // data[World::SuperMario].texture_rect   = sf::IntRect(176, 32, 16, 16);
  // data[World::SuperMario].has_animation_ = false;

  return data;
}
