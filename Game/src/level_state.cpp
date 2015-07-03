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
  this->player = Player(sf::seconds(0.2), true, false);
  if (!player.texture.loadFromFile("assets/gfx/sprite.png")) {
    std::cout << "Error loading image." << std::endl;
    exit(-1);
  }
  // set up the animations for all four directions
  // (set spritesheet and push frames)
  Animation move_right;
  move_right.setSpriteSheet(player.texture);
  move_right.addFrame(sf::IntRect(192, 0, 32, 32));
  move_right.addFrame(sf::IntRect(288, 0, 32, 32));
  player.player_move_left = move_right;

  Animation move_left;
  move_left.setSpriteSheet(player.texture);
  move_left.addFrame(sf::IntRect(320, 0, 32, 32));
  move_left.addFrame(sf::IntRect(352, 0, 32, 32));
  player.player_move_right = move_left;

  current_animation_ = &player.player_move_right;

  // set position
  player.setPosition(sf::Vector2f(100, 100));

  // Initialising the map
  tilemap.tiles.setTexture(tilemap.tileset);
  tiles = tilemap.tiles;
}

void LevelState::draw(const sf::RenderWindow &window) {
  gsm->window.setView(this->view);
  gsm->window.clear(sf::Color::Black);

  gsm->window.draw(tilemap);
  gsm->window.draw(player);
}

void LevelState::update() {
  gsm->window.clear();
  // gsm->window.draw(player);
  // gsm->window.display();
  // gsm->window.draw(player);
}

void LevelState::handleInput() {
  sf::Clock frame_clock;

  float speed          = 150.f;
  bool noKeyWasPressed = true;

  sf::Event event;

  // if a key was pressed set the correct animation and move correctly
  sf::Vector2f movement(0.f, 0.f);

  sf::Time frame_time = frame_clock.restart();

  while (gsm->window.pollEvent(event)) {
    switch (event.type) {
      // Close window
      case sf::Event::Closed:
        gsm->window.close();
        break;

      // Return to Main Menu
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) gsm->popState();
        // break;
        if (event.key.code == sf::Keyboard::Left) {
          current_animation_ = &player.player_move_left;
          movement.x        -= speed;
          noKeyWasPressed    = false;
        }
        if (event.key.code == sf::Keyboard::Right) {
          current_animation_ = &player.player_move_right;
          movement.x        += speed;
          noKeyWasPressed    = false;
        }
        break;
      default: break;
    }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //   current_animation_ = &player.player_move_left;
    //   movement.x        -= speed;
    //   noKeyWasPressed    = false;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    //   current_animation_ = &player.player_move_right;
    //   movement.x        += speed;
    //   noKeyWasPressed    = false;
    // }

    player.play(*current_animation_);
    player.move(movement * frame_time.asSeconds());

    // if no key was pressed stop the animation
    if (noKeyWasPressed) {
      player.stop();
    }
    noKeyWasPressed = true;

    // update AnimatedSprite
    player.update(frame_time);

    // // draw
    gsm->window.clear();
    gsm->window.draw(player);
    // gsm->window.display();
  }
  return;
}

LevelState::~LevelState() {}
