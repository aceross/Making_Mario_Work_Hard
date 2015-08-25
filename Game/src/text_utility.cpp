// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>

#include "../include/text_utility.hpp"


void CentreOrigin(sf::Sprite& sprite) {
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top  + bounds.height / 2.f));
}

void CentreOrigin(sf::Text& text) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                 std::floor(bounds.top + bounds.height / 2.f));
}
