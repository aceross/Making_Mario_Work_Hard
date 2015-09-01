// Copyright 2015, Aaron Ceross

#ifndef INSTANCE_SELECTION_HPP
#define INSTANCE_SELECTION_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "mapfile_handler.hpp"
#include "state.hpp"

class InstanceSelection : public State {
 public:
  InstanceSelection(StateStack& stack, Context context);

  virtual void Draw();
  virtual bool Update(sf::Time dt);
  virtual bool HandleEvent(const sf::Event& event);

  void UpdateOptionText();

 private:
  // Select Pre-Made, Input, Exit
  enum OptionNames { Single, Two, Three, Unsolve, Menu, Exit };

 private:
  sf::Sprite background_sprite_;

  std::vector<sf::Text>  options_;
  std::vector<sf::Text>  instance_options_;
  std::size_t            options_index_;

  MapfileHandler mapfile_handler_;
};

#endif  // INSTANCE_SELECTION_HPP
