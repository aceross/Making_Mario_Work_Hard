// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>

#include "../include/menu_state.hpp"

void MenuState::draw(const sf::RenderWindow &window) {
  this->gsm->window.setView(this->view);
  this->gsm->window.clear(sf::Color::Black);
  this->gsm->window.draw(text);
  return;
}

void MenuState::update(const float dt) {}

void MenuState::handleInput() {
  sf::Event event;

  while (this->gsm->window.pollEvent(event)) {
    switch (event.type) {
      // Close window.
      case sf::Event::Closed: {
        gsm->window.close();
        break;
      }
      default: break;
    }
  }
  return;
}

void MenuState::loadGame() {
  // this->gsm->pushState(GameState *state);
}

MenuState::MenuState(GameStateManager* gsm) {
  this->gsm = gsm;
  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);

  // draw text
  if (!font.loadFromFile("media/font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  text.setString("Splash Screen");
  text.setFont(font);
}

MenuState::~MenuState() {}
