// Copyright 2015, Aaron Ceross

#ifndef TITLE_SCREEN_STATE_HPP
#define TITLE_SCREEN_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.hpp"


class TitleState : public State {
 public:
  TitleState(StateStack& stack, Context context);

  virtual void Draw();
  virtual bool Update(sf::Time delta_time);
  virtual bool HandleEvent(const sf::Event& event);


 private:
  sf::Sprite background_sprite_;
  sf::Text   text_;

  bool        show_text_;
  sf::Time    text_effect_time_;
};

#endif  // TITLE_SCREEN_STATE_HPP
