// Copyright 2015, Aaron Ceross

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm)
: tmx_map_loader_("resources/maps/")
, world(tmx::SfToBoxVec(sf::Vector2f(0.f, 9.8f)))
{
  std::cout << "Welcome to level state" << std::endl;

  this->gsm = gsm;
  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());
  movement_.x = 0.f;
  movement_.y = 0.f;

  // zchaff manager initialisation
  zchaff_manager_.LoadInstance();

  // Setting the main view
  view_.setSize(pos);
  view_.zoom(0.53f);

  // Set the mini map view
  mini_map_.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
  // mini_map_.zoom(3.0f);

  // initialise the level map
  tilemap_.InitialiseMap(zchaff_manager_);
  // assert(tmx_map_loader_.Load("basic_level.tmx"));
  // ml.UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

  // Initialising the Player
  player_ = Player(sf::seconds(1.0), true, false);
  if (!player_.texture.loadFromFile("resources/gfx/mario_bros.png")) {
    std::cout << " Exiting..." << std::endl;
    exit(-1);
  }

  // set up the animations
  // (set spritesheet and push frames)
  Animation move_right;
  move_right.setSpriteSheet(player_.texture);
  move_right.addFrame(sf::IntRect(176, 32, 16, 16));
  move_right.addFrame(sf::IntRect(80, 32, 16, 16));
  move_right.addFrame(sf::IntRect(96, 32, 16, 16));
  player_.player_move_right = move_right;

  Animation move_left;
  move_left.setSpriteSheet(player_.texture);
  move_left.addFrame(sf::IntRect(176, 32, 16, 16));
  move_left.addFrame(sf::IntRect(80, 32, 16, 16));
  move_left.addFrame(sf::IntRect(96, 32, 16, 16));
  player_.player_move_left = move_left;

  Animation jump;
  jump.setSpriteSheet(player_.texture);
  jump.addFrame(sf::IntRect(114, 32, 16, 16));

  current_animation_ = &player_.player_move_right;

  // set position
  player_.setPosition(sf::Vector2f(32, 64));
  player_.position_ = sf::Vector2f(32, 64);
}

void LevelState::InitialiseWorld() {}

void LevelState::draw(const sf::RenderWindow &window) {
  // std::cout << "draw" << std::endl;
  view_.setCenter(player_.getPosition());
  gsm->window.clear(sf::Color::Blue);

  gsm->window.setView(view_);
  // gsm->window.draw(tmx_map_loader_);
  gsm->window.draw(tilemap_);
  gsm->window.draw(player_);

  gsm->window.setView(mini_map_);
  // gsm->window.draw(tmx_map_loader_);
  gsm->window.draw(tilemap_);
}

void LevelState::SolveStart() {
  // for (unsigned int i = 0; i < 4; ++i) {
  //   player_.move(player_.forward_move_);
  //   gsm->window.draw(player_);
  //   std::this_thread::sleep_for (std::chrono::seconds(1));
  // }
  //   player_.move( player_.jump_move_);
  //   gsm->window.draw(player_);
  // // std::this_thread::sleep_for (std::chrono::seconds(4));
  // std::cout << "Jumping" << std::endl;
  // player_.move(player_.fall_move_);
  // gsm->window.draw(player_);
  // std::cout << "Falling" << std::endl;
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

//Thread sleeps for a
void LevelState::update() {
  // player_.update();
  // std::this_thread::sleep_for (std::chrono::seconds(1));
}

void LevelState::handleInput() {
  sf::Clock frame_clock;

  sf::Event event;

  float speed      = 2.5f;
  float fall_speed = 2.5f;

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
        if (event.key.code == sf::Keyboard::Left) {
          current_animation_  = &player_.player_move_left;
          no_key_pressed_    = false;
          player_.moving_left_ = true;
          movement.x -= speed;
          player_.falling_     = true;
          player_.play(*current_animation_);
        }
        if (event.key.code == sf::Keyboard::Right) {
          current_animation_   = &player_.player_move_right;
          no_key_pressed_      = false;
          player_.moving_right_ = true;
          movement.x += speed;
          player_.falling_      = true;
          player_.play(*current_animation_);
        }
        if (event.key.code == sf::Keyboard::Up) {
          current_animation_   = &player_.player_move_right;
          no_key_pressed_      = false;
          player_.moving_right_ = true;
          movement.y += speed;
          player_.falling_      = true;
          player_.play(*current_animation_);
        }
        if (event.key.code == sf::Keyboard::Down) {
          current_animation_   = &player_.player_move_right;
          no_key_pressed_      = false;
          player_.moving_right_ = true;
          movement.y -= speed;
          player_.falling_      = true;
          player_.play(*current_animation_);
        }
        if (event.key.code == sf::Keyboard::Space) {
          current_animation_   = &player_.player_move_right;
          no_key_pressed_      = false;
          player_.jumping_      = true;
          player_.falling_      = false;
        }
        if (event.key.code == sf::Keyboard::S) {
          current_animation_   = &player_.player_move_right;
          no_key_pressed_      = false;
          player_.jumping_      = true;
          player_.falling_      = false;
          SolveStart();
        }
        break;
      default: break;
    }

    player_.play(*current_animation_);
    // player.UpdatePosition(movement);
    // player.move(movement);

    // if no key was pressed stop the animation
    if (no_key_pressed_) {
      player_.stop();
    }
    no_key_pressed_ = true;

    // update AnimatedSprite
    player_.UpdateAnimation(frame_time);
  }

  // // Handle Collision
  // std::vector<tmx::MapLayer>& layers = tmx_map_loader_.GetLayers();
  // for (auto& layer : layers) {
  //
  //   if (layer.type == tmx::ObjectGroup) {
  //
  //     for (auto& object : layer.objects) {
  //
  //       if (layer.name == "Walls") {
  //         // std::cout << "In Walls layer" << std::endl;
  //
  //         // for (auto& point : player.collision_points_) {
  //
  //           if (object.Contains(player_.position_)) {
  //             std::cout << "Collision" << std::endl;
  //           }
  //       }
  //     }
  //   }
  // }

  player_.move(movement);
  // player.UpdatePosition(movement);
}

LevelState::~LevelState() {}
