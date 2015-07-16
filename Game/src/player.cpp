// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <vector>

#include "../include/player.hpp"
#include "../include/resource_manager.hpp"
#include "../include/data_table.hpp"

using namespace std::placeholders;
//
// namepace {
//   const std::vector<PlayerData> Table = InitialisePlayerData();
// }

Player::Player(Type type, const TextureHolder& textures, const FontHolder& fonts)
: type_(type)
, sprite_(textures.Get(Table[type].texture, Table[type].textureRect))
, clauses_false_(0)
, clauses_true_(0)
{}

void Player::DrawCurrent(sf::RenderTarget &target,
                         sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void Player::UpdateCurrent(sf::Time delta_time, CommandQueue& commands) {
  // Update texts and animations
  UpdateTexts();
  UpdateAnimation();

  // Update enemy movement pattern; apply velocity
  UpdateMovementPattern(delta_time);
  Entity::UpdateCurrent(delta_time, commands);
}

sf::FloatRect Player::GetBoundingRect() const {
  return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Player::UpdateAnimation() {
  // if (Table[type_].HasAnimation) {
  //   sf::IntRect texture_rect = Table[type].texture_rect_;
  //
  //   if (Get)
  // }
}
