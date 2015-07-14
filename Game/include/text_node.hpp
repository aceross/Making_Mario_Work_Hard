// Copyright 2015, Aaron Ceross

#ifndef TEXT_NODE_HPP
#define TEXT_NODE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>

#include "resource_manager.hpp"
#include "resource_identifiers.hpp"
#include "scene_node.hpp"

class TextNode : public SceneNode {
 public:
  explicit TextNode(const FontHolder& fonts, const std::string& text);
  void SetString(const std::string& text);

 private:
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::Text text_;
};

#endif  // TEXT_NODE_HPP
