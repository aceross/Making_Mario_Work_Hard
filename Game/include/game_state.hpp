// Copyright 2015, Aaron Ceross

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState {
 public:
  GameState();
  virtual ~GameState();
  virtual void LoadContent();
  virtual void UnloadContent();
  virtual void Update();
  virtual void Draw(sf::RenderWindow &Window);
};

#endif  // GAMESTATE_HPP
