// Copyright 2015, Aaron Ceross

#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "state.hpp"

class MenuState : public State {
 public:
  MenuState(StateStack& stack, Context context);

  virtual void Draw();
  virtual bool Update(sf::Time dt);
  virtual bool HandleEvent(const sf::Event& event);

  void UpdateOptionText();

 private:
  enum OptionNames { Play, Exit };

 private:
  sf::Sprite background_sprite_;

  std::vector<sf::Text>  options_;
  std::size_t        options_index_;
};

#endif  // MENU_STATE_HPP
