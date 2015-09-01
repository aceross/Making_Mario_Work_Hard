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

  void UpdateOptionText();

private:
 // Select Pre-Made, Input, Exit
 enum OptionNames { Resume, Menu, New, Exit };

 private:
  sf::Sprite background_sprite_;
  sf::Text paused_text_;
  sf:: Text instruction_text_;
  // GUI::Container GUI_Container_;

  std::vector<sf::Text>  options_;
  std::vector<sf::Text>  pause_options_;
  std::size_t            options_index_;
};

#endif  // PAUSE_STATE_HPP
