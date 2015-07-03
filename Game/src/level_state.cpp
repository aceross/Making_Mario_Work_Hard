// Copyright 2015, Aaron Ceross

#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm) {
  printf("Welcome to level state.\n");

  this->gsm = gsm;

  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());

  // Setting the view
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);

  // Initialising the Player
  if (!player.texture.loadFromFile("assets/gfx/sprite.png")) {
    std::cout << "Error loading image." << std::endl;
  }
  player.sprite.setTexture(player.texture);

  // Initialising the map
  tilemap.tiles.setTexture(tilemap.tileset);
  tiles = tilemap.tiles;
}

void LevelState::draw(const sf::RenderWindow &window) {
  gsm->window.setView(this->view);
  gsm->window.clear(sf::Color::Black);

  gsm->window.draw(tilemap);
  gsm->window.draw(player.sprite);
}

void LevelState::update() {}

void LevelState::handleInput() {
  sf::Event event;

  while (gsm->window.pollEvent(event)) {
    switch (event.type) {
      // Close window
      case sf::Event::Closed:
        gsm->window.close();
        break;

      // Return to Main Menu
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) gsm->popState();
        break;
      default: break;
    }
  }
  return;
}

LevelState::~LevelState() {}
