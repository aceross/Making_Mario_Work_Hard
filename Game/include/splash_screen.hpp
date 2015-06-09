// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_state.hpp"

class SplashScreen : public GameState {
 public:
  SplashScreen();
  ~SplashScreen();
  virtual void LoadContent();
  virtual void UnloadContent();
  virtual void Update();
  virtual void Draw(sf::RenderWindow &Window);

 private:
  sf::Text text;
  sf::Font font;
};
