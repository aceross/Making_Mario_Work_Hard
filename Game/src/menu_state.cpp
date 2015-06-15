// Copyright 2015, Aaron Ceross

#include "../include/menu_state.hpp"
#include "../include/help_state.hpp"
#include "../include/level_state.hpp"

void MenuState::draw(const sf::RenderWindow &window) {
  this->gsm->window.setView(this->view);
  this->gsm->window.clear(sf::Color::Black);

  for (size_t i = 0; i < NUM_OPTIONS; ++i) {
    this->gsm->window.draw(options[i]);
  }
  return;
}

void MenuState::moveUp() {
  if (this->selection - 1 >= 0) {
    options[this->selection].setColor(sf::Color::White);
    --this->selection;
    // if (this->selection < 0) this->selection = 0;
    options[this->selection].setColor(sf::Color::Yellow);
  }
}

void MenuState::moveDown() {
  if (this->selection + 1 < NUM_OPTIONS) {
    options[this->selection].setColor(sf::Color::White);
    ++this->selection;
    options[this->selection].setColor(sf::Color::Yellow);
    // if (this->selection >= NUM_OPTIONS) this->selection = 0;
  }
}

void MenuState::update() {}
void MenuState::handleInput() {
  sf::Event event;

  while (this->gsm->window.pollEvent(event)) {
    switch (event.type) {
      // Close window.
      case sf::Event::Closed:
        gsm->window.close();
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Up)   moveUp();
        if (event.key.code == sf::Keyboard::Down) moveDown();
        if (event.key.code == sf::Keyboard::Return) {
          if (this->selection == 0) {
            printf("Play selected\n");
            this->gsm->pushState(new LevelState(this->gsm));
          }
          if (this->selection == 1) {
            printf("Help selected\n");
            this->gsm->pushState(new HelpState(this->gsm));
          }
          if (this->selection == 2) {
            printf("Quit selected\n");
            this->gsm->window.close();
            this->gsm->game_over = true;
          }
        }
        break;
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

  // Initialise the selection highlight
  this->selection = 0;

  // Load menu font
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
