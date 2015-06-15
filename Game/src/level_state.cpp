// Copyright 2015, Aaron Ceross

#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm) {
  printf("Welcome to level state.\n");
  this->gsm = gsm;
  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);

  if (!font.loadFromFile("media/font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  text.setString("Press ESC to return to menu.");
  text.setColor(sf::Color::White);
  text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void LevelState::draw(const sf::RenderWindow &window) {
  // this->gsm->window.setView(this->view);
  this->gsm->window.clear(sf::Color::Black);

  this->gsm->window.draw(text);
}

void LevelState::handleInput() {
  sf::Event event;

  while (this->gsm->window.pollEvent(event)) {
    switch (event.type) {
      // Close window
      case sf::Event::Closed:
        this->gsm->window.close();
        break;

      // Return to Main Menu
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) this->gsm->popState();
        break;
      default: break;
    }
  }
  return;
}

void LevelState::update() {}

LevelState::~LevelState() {}
