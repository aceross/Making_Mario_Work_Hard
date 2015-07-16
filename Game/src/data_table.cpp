// Copyright 2015, Aaron Ceross

#include <vector>

#include "../include/data_table.hpp"
#include "../include/player.hpp"

using namespace std::placeholders;

std::vector<PlayerData> InitialisePlayerData() {
  std::vector<PlayerData> data(Player::TypeCount);

  data[Player::SmallPlayer].speed = 32.0f;
  data[Player::SmallPlayer].texture = Textures::Entities;
  // Needs to be updated
  data[Player::SmallPlayer].texture_rect = sf::IntRect(0, 0, 48, 64);
  data[Player::SmallPlayer].has_animation_ = true;

  return data;
}
