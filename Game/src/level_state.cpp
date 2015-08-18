// Copyright 2015, Aaron Ceross

#include <vector>
#include <iostream>
#include "../include/level_state.hpp"

LevelState::LevelState(GameStateManager* gsm)
: ml("resources/maps/")
, world(tmx::SfToBoxVec(sf::Vector2f(0.f, 9.8f)))
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

  // Set the mini map view
  // mini_map_.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

  // initialise the level map
  this->tilemap.InitialiseMap();
  assert(ml.Load("simple_collision_test.tmx"));
  // ml.UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

  // zchaff manager initialisation
  zchaff_manager_.LoadInstance();

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
  move_left.addFrame(sf::IntRect(176, 32, 16, 16));
  move_left.addFrame(sf::IntRect(80, 32, 16, 16));
  move_left.addFrame(sf::IntRect(96, 32, 16, 16));
  player.player_move_left = move_left;

  current_animation_ = &player.player_move_right;

  // set position
  player.setPosition(sf::Vector2f(96, 160));
  player.position_ = sf::Vector2f(96, 160);
}

void LevelState::InitialiseWorld() {
  std::vector<std::unique_ptr<sf::Shape>> debugBoxes;
  std::vector<DebugShape> debugShapes;
  std::map<b2Body*, sf::CircleShape> dynamicShapes; //we can use raw pointers because box2D manages its own memory

  std::vector<tmx::MapLayer>& layers = ml.GetLayers();
  for (auto& layer : layers) {
    if (layer.type == tmx::ObjectGroup) {
      for (auto& object : layer.objects) {
        if (layer.name == "Walls") {
          b2Body* b = tmx::BodyCreator::Add(object, world);
          //iterate over body info to create some visual debugging shapes to help visualise
          debugBoxes.push_back(std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(6.f, 6.f))));
          sf::Vector2f pos = tmx::BoxToSfVec(b->GetPosition());
          debugBoxes.back()->setPosition(pos);
          debugBoxes.back()->setOrigin(3.f, 3.f);

          for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
            b2Shape::Type shapeType = f->GetType();
            if (shapeType == b2Shape::e_polygon) {
              DebugShape ds;
              ds.setPosition(pos);
              b2PolygonShape* ps = (b2PolygonShape*)f->GetShape();
              int count = ps->GetVertexCount();
              for (int i = 0; i < count; i++)
                ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(i)), sf::Color::Green));

              ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(0)), sf::Color::Green));
              debugShapes.push_back(ds);
            }


              }
          }
        }
      }
    }
  }

void LevelState::draw(const sf::RenderWindow &window) {
  view.setCenter(player.getPosition());
  gsm->window.setView(this->view);

  gsm->window.clear(sf::Color::Blue);
  gsm->window.draw(ml);
  // gsm->window.draw(tilemap);
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
    // player.UpdatePosition(movement);
    // player.move(movement);

    // if no key was pressed stop the animation
    if (noKeyWasPressed_) {
      player.stop();
    }
    noKeyWasPressed_ = true;

    // update AnimatedSprite
    player.UpdateAnimation(frame_time);
  }

  // Handle Collision
  std::vector<tmx::MapLayer>& layers = ml.GetLayers();
  for (auto& layer : layers) {

    if (layer.type == tmx::ObjectGroup) {

      for (auto& object : layer.objects) {

        if (layer.name == "Walls") {
          // std::cout << "In Walls layer" << std::endl;

          // for (auto& point : player.collision_points_) {

            if (object.Contains(player.position_)) {
              std::cout << "Collision" << std::endl;
            }
          // }








          // Down Collision
          // if (object.Contains(sf::Vector2f(player.position_.x, player.position_.y +
          //                                  player.getGlobalBounds().height * 2))) {
          //   std::cout << "Gravity Collision" << std::endl;
          // }

          // Left
          // if(object.Contains(sf::Vector2f(player.position_.x - player.getGlobalBounds().width/2 - 1,
          //                                 player.position_.y))) {
          //     std::cout << "Left Collision" << std::endl;
          // } else {
          //
          // }
          //
          // // Right
          // if(object.Contains(sf::Vector2f(player.position_.x - player.getGlobalBounds().width/2 + 1,
          //                                 player.position_.y))) {
          //     std::cout << "Right Collision" << std::endl;
          // }
        }
      }
    }
  }

  player.move(movement);
  // player.UpdatePosition(movement);
}

LevelState::~LevelState() {}
