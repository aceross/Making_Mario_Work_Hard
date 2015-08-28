// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <memory>
// #include <thread>
// #include <chrono>

#include "../include/level.hpp"

Level::Level(sf::RenderTarget& output_target, FontHolder& fonts)
: target_(output_target)
, scene_texture_()
, level_view_(output_target.getDefaultView())
, textures_()
, fonts_(fonts)
, scene_graph_()
, scene_layers_()
, level_bounds_(0.f, 0.f, level_view_.getSize().x, level_view_.getSize().y)
, start_position_(0, 32)
, movement_speed_(2.5f)
, player_mario_(nullptr)
, level_complete_(false)
, display_solution(false)
{
  scene_texture_.create(target_.getSize().x, target_.getSize().y);
  // Start and load SAT solver
  zchaff_manager_.LoadInstance();

  // init level instance
  LoadTextures();
  BuildScene();

  // Prepare the main view and the mini-map
  level_view_.setCenter(player_mario_->getPosition());
  level_view_.zoom(0.57f);
  mini_map_.setViewport(sf::FloatRect(0.72f, 0, 0.23f, 0.23f));
}

void Level::Update(sf::Time delta_time) {
  if (!command_queue_.IsEmpty()) {
    scene_graph_.OnCommand(command_queue_.Pop(), delta_time);
  }

  // Collision detection and response (may destroy entities)
  // HandleCollisions();
  // Regular update step, adapt position (correct if outside view)
  scene_graph_.Update(delta_time, command_queue_);
}

void Level::draw() {
  // draw the main view level
  level_view_.setCenter(player_mario_->getPosition());
  target_.setView(level_view_);
  target_.draw(scene_graph_);

  // draw the mini map view
  target_.setView(mini_map_);
  target_.draw(scene_graph_);
}

CommandQueue& Level::GetCommandQueue() {
  return command_queue_;
}

void Level::LoadTextures() {
  textures_.Load(Textures::Mario, "resources/gfx/mario_bros.png");
  textures_.Load(Textures::Koopa, "resources/gfx/enemies.png");
  textures_.Load(Textures::World, "resources/gfx/tile_set.png");
}

void Level::BuildScene() {
  // Initialise the different layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    Category::Type category = Category::None;
    SceneNode::Ptr layer(new SceneNode(category));
    scene_layers_[i] = layer.get();
    scene_graph_.AttachChild(std::move(layer));
  }

  // Read in the tile map
  tile_map_.InitialiseMap(zchaff_manager_);
  std::cout << "Tilemap Initialised in LEVEL" << std::endl;

  std::unique_ptr<MapNode> map_node(new MapNode());
  map_node->tile_map_.InitialiseMap(zchaff_manager_);
  scene_layers_[Background]->AttachChild(std::move(map_node));

  // Add player sprite
  std::unique_ptr<Mario> player(new Mario(Mario::SmallMario, textures_, fonts_));
  player_mario_ = player.get();
  player_mario_->setPosition(start_position_);
  scene_layers_[Foreground]->AttachChild(std::move(player));
}

void Level::AdaptPlayerPosition() {}

void Level::HandleCollisions() {}

TileMap& Level::GetTileMap() {
  return tile_map_;
}

VariableManager Level::GetVarManager() {
  return zchaff_manager_.GetVarManager();
}
