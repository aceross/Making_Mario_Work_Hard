// Copyright 2015, Aaron Ceross

#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "container.hpp"
#include "state.hpp"

class PauseState : public State {
 public:
  PauseState(StateStack& stack, Context context);

  virtual void Draw();
  virtual bool Update(sf::Time delta_time);
  virtual bool HandleEvent(const sf::Event& event);

 private:
  sf::Sprite background_sprite_;
  sf::Text paused_text_;
  GUI::Container GUI_Container_;
};

#endif  // PAUSE_STATE_HPP
