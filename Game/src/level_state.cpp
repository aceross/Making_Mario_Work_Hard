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
  this->player = Player(sf::seconds(1.0), true, false);
  if (!player.texture.loadFromFile("assets/gfx/sprite.png")) {
    std::cout << "  Error loading image. Exiting..." << std::endl;
    exit(-1);
  }

  // set up the animations
  // (set spritesheet and push frames)
  Animation move_right;
  move_right.setSpriteSheet(player.texture);
  move_right.addFrame(sf::IntRect(192, 0, 32, 32));
  move_right.addFrame(sf::IntRect(288, 0, 32, 32));
  player.player_move_right = move_right;

  Animation move_left;
  move_left.setSpriteSheet(player.texture);
  move_left.addFrame(sf::IntRect(320, 0, 32, 32));
  move_left.addFrame(sf::IntRect(352, 0, 32, 32));
  player.player_move_left = move_left;

  current_animation_ = &player.player_move_right;

  // set position
  player.setPosition(sf::Vector2f(170, 180));

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
  // update player's position
  // player.bottom = player.getPosition().y + player.getSize().height;
  // player.left   = player.getPosition().x;
  // player.right  = player.getPosition().x + player.getSize().width;
  // player.top    = player.getPosition().y;
  player.update(tilemap.t_map_);
}

void LevelState::handleInput() {
  sf::Clock frame_clock;

  float speed          = 32.0f;
  float jump_speed     = 4.0f;
  // float fall_speed     = 5.2f;
  bool noKeyWasPressed = true;

  sf::Event event;

  // if a key was pressed set the correct animation and move correctly
  // sf::Vector2f movement(0.f, 0.f);

  sf::Time frame_time = frame_clock.restart();

  while (gsm->window.pollEvent(event)) {
    switch (event.type) {
      // Close window
      case sf::Event::Closed:
        gsm->window.close();
        break;

      case sf::Event::KeyPressed:
        // Return to Main Menu
        if (event.key.code == sf::Keyboard::Escape) gsm->popState();

        // Manual movement
        if (event.key.code == sf::Keyboard::Left) {
          current_animation_  = &player.player_move_left;
          player.position_.x -= speed;
          noKeyWasPressed     = false;
          player.moving_left_ = true;
          player.play(*current_animation_);
          player.move(player.position_);
          printf("Player postion x = %f , y = %f\n", player.getPosition().x,
                                                     player.getPosition().y);
        }
        if (event.key.code == sf::Keyboard::Right) {
          current_animation_   = &player.player_move_right;
          player.position_.x  += speed;
          noKeyWasPressed      = false;
          player.moving_right_ = true;
          player.play(*current_animation_);
          player.move(player.position_);
          printf("Player postion x = %f , y = %f\n", player.getPosition().x,
                                                     player.getPosition().y);
        }
        if (event.key.code == sf::Keyboard::Space) {
          current_animation_   = &player.player_move_right;
          player.position_.y  -= jump_speed;
          noKeyWasPressed      = false;
          player.jumping_      = true;
          player.move(player.position_);
          printf("Player postion x = %f , y = %f\n", player.getPosition().x,
                                                     player.getPosition().y);
        }
        break;
      default: break;
    }

    // player.play(*current_animation_);
    // player.move(movement * frame_time.asSeconds());

    // if no key was pressed stop the animation
    if (noKeyWasPressed) {
      player.stop();
    }
    noKeyWasPressed = true;

    // update AnimatedSprite
    player.UpdateAnimation(frame_time);

    // // draw
    // gsm->window.clear();
    // gsm->window.draw(player);
    // gsm->window.display();
  }
  return;
}

LevelState::~LevelState() {}
