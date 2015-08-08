// Copyright 2015, Aaron Ceross

#include <vector>
#include <iostream>
#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm)
: ml("resources/maps/")
{
  std::cout << "Welcome to level state" << std::endl;

  this->gsm = gsm;
  sf::Vector2f pos = sf::Vector2f(this->gsm->window.getSize());
  movement_.x = 0.f;
  movement_.y = 0.f;


  // view.setViewport(sf::FloatRect(200, 300, gsm->window.getSize().x,
  //                                    gsm->window.getSize().y));

  // Setting the main view
  this->view.setSize(pos);
  pos *= 0.5f;
  this->view.setCenter(pos);
  view.zoom(0.57f);

  mini_map_.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

  assert(ml.Load("simple_collision_test.tmx"));
  ml.UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

  // Initialising the Player
  this->player = Player(sf::seconds(1.0), true, false);
  if (!player.texture.loadFromFile("resources/gfx/mario_bros.png")) {
    std::cout << "  Error loading image. Exiting..." << std::endl;
    exit(-1);
  }

  // set up the animations
  // (set spritesheet and push frames)
  Animation move_right;
  move_right.setSpriteSheet(player.texture);
  move_right.addFrame(sf::IntRect(176, 32, 16, 16));
  move_right.addFrame(sf::IntRect(80, 32, 16, 16));
  move_right.addFrame(sf::IntRect(96, 32, 16, 16));
  player.player_move_right = move_right;

  Animation move_left;
  move_left.setSpriteSheet(player.texture);
  move_left.addFrame(sf::IntRect(16, 16, -176, -32));
  move_left.addFrame(sf::IntRect(16, 16, -80, -32));
  move_left.addFrame(sf::IntRect(16, 16, -96, -32));
  player.player_move_left = move_left;

  current_animation_ = &player.player_move_right;

  // // set position
  player.setPosition(sf::Vector2f(96, 160));
  player.position_ = sf::Vector2f(96, 160);
}

void LevelState::draw(const sf::RenderWindow &window) {
  view.setCenter(player.getPosition());
  gsm->window.setView(this->view);

  gsm->window.clear(sf::Color::Blue);
  gsm->window.draw(ml);
  gsm->window.draw(player);
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
          current_animation_  = &player.player_move_left;
          noKeyWasPressed_    = false;
          player.moving_left_ = true;
          movement.x -= speed;
          player.falling_     = true;
          player.play(*current_animation_);
        }
        if (event.key.code == sf::Keyboard::Right) {
          current_animation_   = &player.player_move_right;
          noKeyWasPressed_     = false;
          player.moving_right_ = true;
          movement.x += speed;
          player.falling_      = true;
          player.play(*current_animation_);
        }
        if (event.key.code == sf::Keyboard::Space) {
          current_animation_   = &player.player_move_right;
          noKeyWasPressed_     = false;
          player.jumping_      = true;
          player.falling_      = false;
        }
        break;
      default: break;
    }

    player.play(*current_animation_);
    player.UpdatePosition(movement);
    player.move(movement);

    // if no key was pressed stop the animation
    if (noKeyWasPressed_) {
      player.stop();
    }
    noKeyWasPressed_ = true;

    // update AnimatedSprite
    player.UpdateAnimation(frame_time);
  }

  std::vector<tmx::MapLayer>& layers_ = ml.GetLayers();
  for (auto& layer : layers_) {
    if (layer.type == tmx::ObjectGroup) {
      for (auto& object : layer.objects) {
        if (layer.name == "Walls") {
          std::cout << "Collision is true" << std::endl;
        }
      }
    }

  }


  // std::vector<tmx::MapLayer>& layers = ml.GetLayers();
  //   for(auto& layer : layers)
  //   {
  //       if(layer.type == tmx::ObjectGroup)
  //       {
  //           for(auto& obj : layer.objects)
  //           {
  // // Find the layer named collision
  // if(layer.name == "Collision")
  // {
  //     // Check down / gravity
  //     if(obj.Contains(sf::Vector2f(cameraPos.x, cameraPos.y + player.height*2)))
  //     {
  //         falling = false;
  //     }
  //     else
  //     {
  //         falling = true;
  //         acc.restart();
  //     }
  //     // Left
  //     if(obj.Contains(sf::Vector2f(cameraPos.x - player.width/2 - 1, cameraPos.y)))
  //     {
  //         moveLeft = false;
  //     }
  //     else
  //     {
  //         moveLeft = true;
  //         cout << "Move left is true!" << endl;
  //     }
  //     // Right
  //     if(obj.Contains(sf::Vector2f(cameraPos.x + player.width/2 + 1, cameraPos.y)))
  //     {
  //         moveRight = false;
  //     }
  //     else
  //     {
  //         moveRight = true;
  //         cout << "Move right is true!" << endl;
  //     }
  //               }
  //           }
  //       }
  //   }


  return;
}

LevelState::~LevelState() {}
