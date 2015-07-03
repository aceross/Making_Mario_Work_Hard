// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "map.hpp"

class Player : public sf::Sprite {
 public:
  Player();
  explicit Player(const sf::Texture& t);
  Player(const sf::Texture &t, const sf::IntRect &ir);
  virtual ~Player();
  // void draw(const sf::RenderWindow &window);
  void update();
  void Collision(Entity* entity);

  const sf::Clock& getClock()     { return sprite_clock; }
  const sf::Time&  getDelimiter() { return sprite_clock_delimiter; }
  const std::vector<sf::IntRect>& getSpriteFrames() { return sprite_frames; }
  const sf::IntRect& getSingleFrame(int frame) { return sprite_frames[frame]; }
  void addSpriteFrame(const sf::IntRect &ir)   { sprite_frames.push_back(ir); }

  sf::Sprite  sprite;
  sf::Texture texture;

 private:
  sf::Clock sprite_clock;
  sf::Time  sprite_clock_delimiter;
  std::vector<sf::IntRect> sprite_frames;
  int current_frame;
};

#endif  // PLAYER_HPP
