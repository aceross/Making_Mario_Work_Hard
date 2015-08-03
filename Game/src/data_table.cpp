// Copyright 2015, Aaron Ceross

#include <vector>

#include "../include/data_table.hpp"
#include "../include/player.hpp"

using namespace std::placeholders;

std::vector<PlayerData> InitialisePlayerData() {
  std::vector<PlayerData> data(Player::TypeCount);

  data[Player::SmallPlayer].speed          = 32.0f;
  data[Player::SmallPlayer].hit_points_    = 1; 
  data[Player::SmallPlayer].texture        = Textures::Mario;
  data[Player::SmallPlayer].texture_rect   = sf::IntRect(176, 32, 16, 16);
  data[Player::SmallPlayer].has_animation_ = true;

  return data;
}
