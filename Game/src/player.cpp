// Copyright 2015, Aaron Ceross
#include <SFML/Graphics.hpp>
#include "../include/player.hpp"
#include "../include/game_state_manager.hpp"

Player::Player() {
  if (!this->texture.loadFromFile("media/gfx/sprite.png")) {
    std::cout << "Could not find/load the requested image." << std::endl;
  }

  this->sprite.setTexture(this->texture);
}

void Player::draw(const sf::RenderWindow &window) {}

Player::~Player() {}
