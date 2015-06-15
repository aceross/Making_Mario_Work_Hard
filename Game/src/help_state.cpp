// Copyright 2015, Aaron Ceross
#include <SFML/Graphics.hpp>
#include "../include/help_state.hpp"

HelpState::HelpState(GameStateManager* gsm) {
  printf("Welcome to help state.\n");
  this->gsm = gsm;
  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);

  if (!font.loadFromFile("media/font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  help_text.setColor(sf::Color::White);
  help_text.setString("Press ESC to return to menu.");
}

void HelpState::draw(const sf::RenderWindow &window) {
  this->gsm->window.setView(this->view);
  this->gsm->window.clear(sf::Color::Black);
  this->gsm->window.draw(help_text);
}

void HelpState::handleInput() {
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

void HelpState::update() {}

HelpState::~HelpState() {}
