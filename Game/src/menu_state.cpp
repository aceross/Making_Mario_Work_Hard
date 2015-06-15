// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>

#include "../include/menu_state.hpp"

void MenuState::draw(const sf::RenderWindow &window) {
  this->gsm->window.setView(this->view);
  this->gsm->window.clear(sf::Color::Black);

  for (size_t i = 0; i < NUM_OPTIONS; ++i) {
    this->gsm->window.draw(options[i]);
  }

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

  // Play Game Option
  options[0].setFont(font);
  options[0].setColor(sf::Color::White);
  options[0].setString("Play Game");
  options[0].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT /
                        (NUM_OPTIONS + 1) * 1);

  // Help Option
  options[1].setFont(font);
  options[1].setColor(sf::Color::White);
  options[1].setString("Help");
  options[1].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT /
                        (NUM_OPTIONS + 1) * 2);

// Quit Option
  options[2].setFont(font);
  options[2].setColor(sf::Color::White);
  options[2].setString("Quit");
  options[2].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT /
                        (NUM_OPTIONS + 1) * 3);
}

MenuState::~MenuState() {}
