// Copyright 2015, Aaron Ceross

#include "../include/animation.hpp"

Animation::Animation() : texture_(NULL) {}

void Animation::addFrame(sf::IntRect rect) {
  frames_.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture &texture) {
  texture_ = &texture;
}

const sf::Texture* Animation::getSpriteSheet() const {
  return texture_;
}

std::size_t Animation::getSize() const {
  return frames_.size();
}

const sf::IntRect& Animation::getFrame(std::size_t n) const {
  return frames_[n];
}
