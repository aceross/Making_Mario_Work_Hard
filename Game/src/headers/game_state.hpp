// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>

class GameState {
 public:
  GameState();
  virtual void LoadContent();
  virtual void UnloadContent();
  virtual void Update();
  virtual void Draw(sf::RenderWindow &Window);
};
