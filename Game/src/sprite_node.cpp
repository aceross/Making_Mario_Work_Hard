// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>
#include "../include/sprite_node.hpp"

SpriteNode::SpriteNode(const sf::Texture& texture)
: sprite_(texture)
{}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
: sprite_(texture, textureRect)
{}

void SpriteNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}
