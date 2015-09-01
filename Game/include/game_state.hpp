// Copyright 2015, Aaron Ceross

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.hpp"
#include "level.hpp"
#include "player_manager.hpp"

class GameState : public State {
 public:
  GameState(StateStack& states, Context context);

  virtual void Draw();
  virtual bool Update(sf::Time delta_time);
  virtual bool HandleEvent(const sf::Event& event);

 private:
  Level          level_;
  PlayerManager& player_manager_;
};

#endif  // GAME_STATE_HPP
