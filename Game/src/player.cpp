// Copyright 2015, Aaron Ceross

#include "../include/player.hpp"
#include <vector>

Player::Player(sf::Time frameTime, bool paused, bool looped) :
  animation_(NULL), frame_time_(frameTime), current_frame_(0),
  is_paused_(paused), is_looped_(looped), texture_(NULL) {}

void Player::setAnimation(const Animation& animation) {
  animation_     = &animation;
  texture_       = animation_->getSpriteSheet();
  current_frame_ = 0;
  setFrame(current_frame_);
}

void Player::setFrameTime(sf::Time time) {
  frame_time_ = time;
}

void Player::play() {
  is_paused_ = false;
}

void Player::play(const Animation& animation) {
  if (getAnimation() != &animation) {
    setAnimation(animation);
  }
  play();
}

void Player::pause() {
  is_paused_ = true;
}

void Player::stop() {
  is_paused_     = true;
  current_frame_ = 0;
  setFrame(current_frame_);
}

void Player::setLooped(bool looped) {
  is_looped_ = looped;
}

void Player::setColor(const sf::Color& color) {
  // Update the vertices' color
  vertices_[0].color = color;
  vertices_[1].color = color;
  vertices_[2].color = color;
  vertices_[3].color = color;
}

const Animation* Player::getAnimation() const {
  return animation_;
}

sf::FloatRect Player::getLocalBounds() const {
  sf::IntRect rect = animation_->getFrame(current_frame_);

  float width  = static_cast<float>(std::abs(rect.width));
  float height = static_cast<float>(std::abs(rect.height));

  return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect Player::getGlobalBounds() const {
  return getTransform().transformRect(getLocalBounds());
}

sf::FloatRect Player::getSize() const {
  return getTransform().transformRect(getSize());
}

bool Player::isLooped() const {
  return is_looped_;
}

bool Player::isPlaying() const {
  return !is_paused_;
}

sf::Time Player::getFrameTime() const {
  return frame_time_;
}

void Player::setFrame(std::size_t newFrame, bool resetTime) {
  if (animation_) {
    // calculate new vertex positions and texture coordiantes
    sf::IntRect rect = animation_->getFrame(newFrame);

    vertices_[0].position = sf::Vector2f(0.f, 0.f);
    vertices_[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
    vertices_[2].position = sf::Vector2f(static_cast<float>(rect.width),
                                         static_cast<float>(rect.height));
    vertices_[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

    float left   = static_cast<float>(rect.left) + 0.0001f;
    float right  = left + static_cast<float>(rect.width);
    float top    = static_cast<float>(rect.top);
    float bottom = top + static_cast<float>(rect.height);

    vertices_[0].texCoords = sf::Vector2f(left, top);
    vertices_[1].texCoords = sf::Vector2f(left, bottom);
    vertices_[2].texCoords = sf::Vector2f(right, bottom);
    vertices_[3].texCoords = sf::Vector2f(right, top);
  }

  if (resetTime) {
    current_time_ = sf::Time::Zero;
  }
}

void Player::UpdateAnimation(sf::Time delta_time) {
  // if not paused and we have a valid animation
  if (!is_paused_ && animation_) {
    // add delta time
    current_time_ += delta_time;

    // if current time is bigger then the frame time advance one frame
    if (current_time_ >= frame_time_) {
      // reset time, but keep the remainder
      current_time_ = sf::microseconds(current_time_.asMicroseconds() %
                                       frame_time_.asMicroseconds());

      // get next Frame index
      if (current_frame_ + 1 <= animation_->getSize()) {
        current_frame_++;
      } else {
        // animation has ended
        // reset to start
        current_frame_ = 0;
        if (is_looped_) {
          is_paused_ = true;
        }
      }
      // set the current frame, not reseting the time
      setFrame(current_frame_, false);
    }
  }
}

void Player::update(std::vector<std::vector<Tile>> t_map) {
  // int p_x = position_.x;
  // int p_y = position_.y;

  for (std::vector<std::vector<int>>::size_type i = 0; i < t_map.size(); ++i) {
    for (std::vector<int>::size_type j = 0; j < t_map[i].size(); ++j) {
      if (t_map[i][j].GetTileValue() != 0) {
        if (Collision::Collide(position_, t_map[i][j])) {
          printf("Collision!\n");
        }
      }
    }
  }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (animation_ && texture_) {
    states.transform  *= getTransform();
    states.texture     = texture_;
    target.draw(vertices_, 4, sf::Quads, states);
  }
}
