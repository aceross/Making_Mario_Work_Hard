// Copyright 2015, Aaron Ceross

#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class Animation : public sf::Drawable, public sf::Transformable {
 public:
  Animation();
  explicit Animation(const sf::Texture& texture, sf::IntRect text_rect);

  void SetTexture(const sf::Texture& texture, sf::IntRect text_rect);
  const sf::Texture* GetTexture() const;

  void SetFrameSize(sf::Vector2i frame_size_);
  sf::Vector2i GetFrameSize() const;

  void SetNumFrames(std::size_t num_frames);
  std::size_t GetNumFrames() const;

  void SetDuration(sf::Time duration);
  sf::Time GetDuration() const;

  void SetRepeating(bool flag);
  bool IsRepeating() const;

  void Restart();
  bool IsFinished() const;

  sf::FloatRect GetLocalBounds() const;
  sf::FloatRect GetGlobalBounds() const;

  void Update(sf::Time delta_time);

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::Sprite   sprite_;
  sf::Vector2i frame_size_;
  std::size_t  num_frames_;
  std::size_t  current_frame_;
  sf::Time     duration_;
  sf::Time     elapsed_time_;
  bool repeat_;
};

#endif  // ANIMATION_HPP
