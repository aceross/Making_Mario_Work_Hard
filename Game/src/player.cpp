// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <vector>

#include "../include/player.hpp"
#include "../include/resource_manager.hpp"
#include "../include/data_table.hpp"
#include "../include/command_queue.hpp"

using namespace std::placeholders;

namespace {
  const std::vector<PlayerData> Table = InitialisePlayerData();
}

Player::Player(Type type, const TextureHolder& textures, const FontHolder& fonts)
: type_(type)
, sprite_(textures.Get(Table[type].texture), Table[type].texture_rect)
// , fire_command_()
// , direction_index_(0)
// , clauses_true_(0)
// , clauses_false_(0)
{

}

sf::Vector2i Player::GetLocation() {
  return location_;
}

void Player::UpdateLocation(sf::Vector2i location_update) {
  printf("Original location x = %d, y = %d\n", location_.x, location_.y);
  printf("Location update x = %d, y = %d\n", location_update.x, location_update.y);
  location_ += location_update;
  printf("Location after update x = %d, y = %d\n", location_.x, location_.y);
  printf("\n");
}

void Player::UpdateLocation(int x, int y) {
  location_.x += x;
  location_.y += y;
}

void Player::DrawCurrent(sf::RenderTarget &target,
                         sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void Player::UpdateCurrent(sf::Time delta_time, CommandQueue& commands) {
  // Update texts and animations
  // UpdateTexts();
  UpdateAnimation();

  // Update enemy movement pattern; apply velocity
  // UpdateMovementPattern(delta_time);
  // Entity::UpdateCurrent(delta_time, commands);
}

sf::FloatRect Player::GetBoundingRect() const {
  return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

// May need to update as Jump animation and Walk animation
void Player::UpdateAnimation() {
  if (Table[type_].has_animation_) {
    sf::IntRect texture_rect = Table[type_].texture_rect;

  // Roll left: Texture rect offset once
  if (GetLocation().x < 0) {
    texture_rect.left += texture_rect.width;
  }
  // Roll right: Texture rect offset twice
  else if (GetLocation().x > 0) {
    texture_rect.left += 2 * texture_rect.width;
  }

  sprite_.setTextureRect(texture_rect);
  }
}
