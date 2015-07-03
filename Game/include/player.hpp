// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include "animation.hpp"

class Player : public sf::Drawable, public sf::Transformable {
 public:
  explicit Player(sf::Time frameTime = sf::seconds(0.2f),
                  bool paused = false, bool looped = true);
  void update(sf::Time deltaTime);
  void setAnimation(const Animation& animation);
  void setFrameTime(sf::Time time);
  void play();
  void play(const Animation& animation);
  void pause();
  void stop();
  void setLooped(bool looped);
  void setColor(const sf::Color& color);
  const Animation* getAnimation() const;
  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;
  bool isLooped() const;
  bool isPlaying() const;
  sf::Time getFrameTime() const;
  void setFrame(std::size_t newFrame, bool resetTime = true);

  Animation player_move_left;
  Animation player_move_right;

  void handleInput();

  sf::Texture texture;
  // AnimationHandler animation_handler_;

 private:
  const Animation* animation_;
  sf::Time frame_time_;
  sf::Time current_time_;
  std::size_t current_frame_;
  bool is_paused_;
  bool is_looped_;
  const sf::Texture* texture_;
  sf::Vertex vertices_[4];

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // PLAYER_HPP
