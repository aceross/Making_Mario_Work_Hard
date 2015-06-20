// Copyright 2015, Aaron Ceross

#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm) {
  printf("Welcome to level state.\n");

  this->gsm        = gsm;
  this->player     = Player();
  this->tilemap    = TileMap();

  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());

  // Setting the view
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);

  // Drawing the Player
  if (!this->player.texture.loadFromFile("assets/gfx/sprite.png")) {
    std::cout << "Error loading image." << std::endl;
  }
  this->player.sprite.setTexture(this->player.texture);

  // Loading the map
  this->tilemap.loadMap();
  this->tilemap.setTiles();
  this->tilemap.tiles.setTexture(this->tilemap.tile_Texture);
  this->tiles = this->tilemap.tiles;
}

void LevelState::draw(const sf::RenderWindow &window) {
  this->gsm->window.setView(this->view);
  this->gsm->window.clear(sf::Color::Black);

  this->gsm->window.draw(tiles);
  this->gsm->window.draw(player.sprite);
}

void LevelState::update() {}

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

LevelState::~LevelState() {}
