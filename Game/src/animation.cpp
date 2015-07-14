// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../include/animation.hpp"

Animation::Animation()
: sprite_()
, frame_size_()
, num_frames_(0)
, current_frame_(0)
, duration_(sf::Time::Zero)
, elapsed_time_(sf::Time::Zero)
, repeat_(false)
{}

Animation::Animation(const sf::Texture& texture)
: sprite_(texture)
, frame_size_()
, num_frames_(0)
, current_frame_(0)
, duration_(sf::Time::Zero)
, elapsed_time_(sf::Time::Zero)
, repeat_(false)
{}

void Animation::SetTexture(const sf::Texture &texture) {
  sprite_.setTexture(texture);
}

const sf::Texture* Animation::GetTexture() const {
  return sprite_.getTexture();
}

void Animation::SetFrameSize(sf::Vector2i frame_size) {
  frame_size_ = frame_size;
}

sf::Vector2i Animation::GetFrameSize() const {
  return frame_size_;
}

void Animation::SetNumFrames(std::size_t num_frames) {
  num_frames_ = num_frames;
}

std::size_t Animation::GetNumFrames() const {
  return num_frames_;
}

void Animation::SetDuration(sf::Time duration) {
  duration_ = duration;
}

sf::Time Animation::GetDuration() const {
  return duration_;
}

void Animation::SetRepeating(bool flag) {
  repeat_ = flag;
}

bool Animation::IsRepeating() const {
  return repeat_;
}

void Animation::Restart() {
  current_frame_ = 0;
}

bool Animation::IsFinished() const {
  return current_frame_ >= num_frames_;
}

sf::FloatRect Animation::GetLocalBounds() const {
  return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(GetFrameSize()));
}

sf::FloatRect Animation::GetGlobalBounds() const {
  return getTransform().transformRect(GetGlobalBounds());
}

void Animation::Update(sf::Time delta_time) {
  sf::Time time_per_frame = duration_ / static_cast<float>(num_frames_);
  elapsed_time_ += delta_time;

  sf::Vector2i texture_bounds(sprite_.getTexture()->getSize());
  sf::IntRect texture_rect = sprite_.getTextureRect();

  if (current_frame_ == 0) {
    texture_rect = sf::IntRect(0, 0, frame_size_.x, frame_size_.y);
  }
  while (elapsed_time_ >= time_per_frame &&
                                 (current_frame_ <= num_frames_ || repeat_)) {
    // Move the texture rect left
    texture_rect.left += texture_rect.width;

    // If the end of the texture is reached
    if (texture_rect.left +texture_rect.width > texture_bounds.x) {
      // Move it down one line
      texture_rect.left = 0;
      texture_rect.top += texture_rect.height;
    }

    // Progress to the next frame
    elapsed_time_ -= time_per_frame;

    if (repeat_) {
      current_frame_ = (current_frame_ + 1) % num_frames_;

      if (current_frame_ == 0) {
        texture_rect = sf::IntRect(0, 0, frame_size_.x, frame_size_.y);
      }
    } else {
      ++current_frame_;
    }
  }

  sprite_.setTextureRect(texture_rect);
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(sprite_, states);
}
