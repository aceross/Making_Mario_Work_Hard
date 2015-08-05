// Copyright 2015, Aaron Ceross

#include <vector>
#include <iostream>
#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm)
: ml("assets/maps/")
{
  std::cout << "Welcome to level state" << std::endl;

  this->gsm = gsm;
  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());
  movement_.x = 0.f;
  movement_.y = 0.f;

  // Setting the view
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);

  // this->tilemap.initialiseMap();
  assert(ml.Load("fulllevel.tmx"));

  // Initialising the Player
  // this->player = Player(sf::seconds(1.0), true, false);
  // if (!player.texture.loadFromFile("assets/gfx/sprite.png")) {
  //   std::cout << "  Error loading image. Exiting..." << std::endl;
  //   exit(-1);
  // }

  // set up the animations
  // (set spritesheet and push frames)
  // Animation move_right;
  // move_right.setSpriteSheet(player.texture);
  // move_right.addFrame(sf::IntRect(192, 0, 32, 32));
  // move_right.addFrame(sf::IntRect(288, 0, 32, 32));
  // player.player_move_right = move_right;
  //
  // Animation move_left;
  // move_left.setSpriteSheet(player.texture);
  // move_left.addFrame(sf::IntRect(320, 0, 32, 32));
  // move_left.addFrame(sf::IntRect(352, 0, 32, 32));
  // player.player_move_left = move_left;
  //
  // current_animation_ = &player.player_move_right;
  //
  // // set position
  // player.setPosition(sf::Vector2f(64, 192));
  // player.position_ = sf::Vector2f(64, 192);

  // Initialising the map
  // tilemap.tiles.setTexture(tilemap.tileset);
  // tiles = tilemap.tiles;
}

void LevelState::draw(const sf::RenderWindow &window) {
  gsm->window.setView(this->view);
  gsm->window.clear(sf::Color::Black);

  // gsm->window.draw(tilemap);
  gsm->window.draw(ml);

  // gsm->window.draw(player);
}

bool LevelState::HasCollision(Player p, Tile t) {
  // sf::FloatRect player = p.getGlobalBounds();
  //
  // if (player.contains(t.GetTilePosition())) {
  //   std::cout << "Intersection" << std::endl;
  //   return true;
  // }
  return false;
}

void LevelState::ManageCollision() {}

void LevelState::update() {}

void LevelState::handleInput() {
  sf::Clock frame_clock;

  sf::Event event;

  float speed         = 5.0f;
  float fall_speed    = 5.2f;

  // if a key was pressed set the correct animation and move correctly
  sf::Vector2f movement(0.f, 0.f);

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
        // if (event.key.code == sf::Keyboard::Left) {
        //   current_animation_  = &player.player_move_left;
        //   noKeyWasPressed_    = false;
        //   player.moving_left_ = true;
        //   // player.falling_     = true;
        //   player.play(*current_animation_);
        // }
        // if (event.key.code == sf::Keyboard::Right) {
        //   current_animation_   = &player.player_move_right;
        //   noKeyWasPressed_     = false;
        //   player.moving_right_ = true;
        //   player.play(*current_animation_);
        // }
        // if (event.key.code == sf::Keyboard::Space) {
        //   current_animation_   = &player.player_move_right;
        //   noKeyWasPressed_     = false;
        //   player.jumping_      = true;
        //   player.falling_      = false;
        // }
        break;
      default: break;
    }

    // player.play(*current_animation_);
    // player.UpdatePosition(movement);

    // printf("Player postion before collision loop : x = %f , y = %f\n",
    //         player.getPosition().x, player.getPosition().y);
    //
    // // Collision rules
    // for (int i = 0; i < tilemap.height; ++i) {
    //   for (int j = 0; j < tilemap.width; ++j) {
    //     if (tilemap.t_map_[i][j].GetTileValue() != 0) {
    //       // printf("tile position x = %d\n", tile );
    //
    //       if (HasCollision(player, tilemap.t_map_[i][j])) {
    //         std::cout << "Collision" << std::endl;
    //         if (player.moving_left_) {
    //           std::cout << "Left Collision" << std::endl;
    //           player.moving_left_ = false;
    //         }
    //       }
    //       if (player.moving_left_) {
    //         movement.x -= speed;
    //         player.moving_left_ = false;
    //       }
    //       if (player.moving_right_) {
    //         movement.x += speed;
    //         player.moving_right_ = false;
    //       }
    //       if (player.falling_) {
    //         movement.y += fall_speed;
    //       }
    //     }
    //   }  // End of innter for loop
    // }  // End of outer for loop
    //
    // player.move(movement);
    //
    // printf("Player postion AFTER loop x = %f , y = %f\n",
    //         player.getPosition().x, player.getPosition().y);
    //
    // // if no key was pressed stop the animation
    // if (noKeyWasPressed_) {
    //   player.stop();
    // }
    // noKeyWasPressed_ = true;
    //
    // // update AnimatedSprite
    // player.UpdateAnimation(frame_time);

    // // draw
    // gsm->window.clear();
    // gsm->window.draw(player);
    // gsm->window.display();
  }
  return;
}

LevelState::~LevelState() {}
