// Copyright 2015, Aaron Ceross

#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "scene_node.hpp"

class SpriteNode : public SceneNode {
 public:
  explicit SpriteNode(const sf ::Texture& texture);
  SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

 private:
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::Sprite sprite_;
};

#endif  // SPRITE_NODE_HPP
