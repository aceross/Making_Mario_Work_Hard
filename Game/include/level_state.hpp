// Copyright 2015, Aaron Ceross

#ifdef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include "game_state.hpp"

class LevelState : public GameState {
 private:
  sf::View view;

 public:
  virtual void draw(const sf::RenderWindow &window);
  virtual void update(const float dt);
  virtual void handleInput();

  explicit LevelState(GameStateManager* gsm);
  virtual ~LevelState();
};

#endif  // LEVEL_STATE_HPP
