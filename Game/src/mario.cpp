// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <vector>
// #include <thread>
// #include <chrono>

#include "../include/mario.hpp"
#include "../include/resource_manager.hpp"
#include "../include/data_table.hpp"
#include "../include/command_queue.hpp"
#include "../include/command.hpp"

using namespace std::placeholders;

namespace {
  const std::vector<PlayerData> Table = InitialisePlayerData();
}

Mario::Mario(Type type, const TextureHolder& textures, const FontHolder& fonts)
: sprite_(textures.Get(Table[type].texture), Table[type].texture_rect)
, navigator_()
, type_(type)
, waiting_(false)
{
  // navigator_
}

float Mario::GetSpeed() const {
  return Table[type_].speed;
}

sf::Vector2f Mario::GetLocation() {
  return location_;
}

void Mario::UpdateLocation(sf::Vector2f location_update) {
  move(location_update);
  location_ += location_update;
}

void Mario::UpdateLocation(int x, int y) {
  location_.x += x;
  location_.y += y;
  move(x, y);
}

void Mario::HandleCollision() {

}

void Mario::DrawCurrent(sf::RenderTarget &target,
                         sf::RenderStates states) const {

  target.draw(sprite_, states);
}

void Mario::UpdateCurrent(sf::Time delta_time, CommandQueue& commands) {
}

unsigned int Mario::GetCategory() const {
  return Category::MarioPlayer;
}

sf::FloatRect Mario::GetBoundingRect() const {
  return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Mario::MoveMario(sf::Vector2f location_update) {
  move(location_update);
}

// May need to update as Jump animation and Walk animation
void Mario::UpdateAnimation() {
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

void Mario::InitialiseLevelNavigator(TileMap tm) {
  navigator_.GetTileMap(tm);
  std::cout << "TileMap Attained" << std::endl;
}
