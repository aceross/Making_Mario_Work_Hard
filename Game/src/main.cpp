/*------------------------------------------------------------------------------
    Copyright 2015, Aaron Ceross

    Source code submitted for the MSc Thesis, as part of the
    completion of the MSc in Computer Science at the University of Bristol
------------------------------------------------------------------------------*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game_state_manager.hpp"

int main() {
  sf::RenderWindow Window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
                          "Making Mario Work Hard");
  GameStateManager::GetInstance().Initialise();
  GameStateManager::GetInstance().LoadContent();

  // game loop
  while (Window.isOpen()) {
    sf::Event event;
    if (Window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          event.key.code == sf::Keyboard::Escape) {
        Window.close();
      }
      if (event.key.code ==sf::Keyboard::S) {
        GameStateManager::GetInstance().AddState(new SplashScreen());
      }
      if (event.key.code ==sf::Keyboard::T) {
        GameStateManager::GetInstance().AddState(new TitleScreen());
      }
    }
    GameStateManager::GetInstance().Update();
    GameStateManager::GetInstance().Draw(Window);
    Window.display();
  }

  return 0;
}
