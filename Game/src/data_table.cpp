// Copyright 2015, Aaron Ceross

#include <vector>

#include "../include/data_table.hpp"
#include "../include/player.hpp"

using namespace std::placeholders;

std::vector<PlayerData> InitialisePlayerData() {
  std::vector<PlayerData> data(Player::TypeCount);

  data[Player::SmallMario].speed          = 2.5f;
  data[Player::SmallMario].hit_points_    = 1;
  data[Player::SmallMario].texture        = Textures::Mario;
  data[Player::SmallMario].texture_rect   = sf::IntRect(176, 32, 16, 16);
  data[Player::SmallMario].has_animation_ = false;

  data[Player::SuperMario].speed          = 2.5f;
  data[Player::SuperMario].hit_points_    = 1;
  data[Player::SuperMario].texture        = Textures::Mario;
  data[Player::SuperMario].texture_rect   = sf::IntRect(176, 32, 16, 16);
  data[Player::SuperMario].has_animation_ = false;

  return data;
}
