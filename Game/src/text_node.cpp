// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>

#include "../include/text_node.hpp"
#include "../include/text_centring.hpp"

TextNode::TextNode(const FontHolder& fonts, const std::string& text) {
  text_.setFont(fonts.Get(Fonts::Main));
  text_.setCharacterSize(20);
  SetString(text);
}

void TextNode::DrawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const {
  target.draw(text_, states);
}

void TextNode::SetString(const std::string& text) {
  text_.setString(text);
  CentreOrigin(text_);
}
