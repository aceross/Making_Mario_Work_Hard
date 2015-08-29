// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <memory>

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
, mario_position_(0, 32)
, movement_speed_(2.5f)
, player_mario_(nullptr)
, level_complete_(false)
, display_solution(false)
, in_start_gadget_(false)
, in_variable_gadget_(false)
, in_warp_gadget_(false)
, finished_warps_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
{
  scene_texture_.create(target_.getSize().x, target_.getSize().y);

  // Start and load SAT solver
  zchaff_manager_.LoadInstance();
  variable_managaer_ = zchaff_manager_.GetVarManager();

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
    Command c = command_queue_.Front();
    AdaptPlayerPosition(c.location_, c.var_assignment_);
    scene_graph_.OnCommand(command_queue_.Pop(), delta_time);
  }

  // Collision detection and response
  HandleCollisions();
  // Update scene graph and child layers
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

  std::unique_ptr<MapNode> map_node(new MapNode());
  map_node->tile_map_.InitialiseMap(zchaff_manager_);
  scene_layers_[Background]->AttachChild(std::move(map_node));

  // Add world Objects


  // Add player sprite
  std::unique_ptr<Mario> player(new Mario(Mario::SmallMario, textures_, fonts_));
  player_mario_ = player.get();
  player_mario_->setPosition(mario_position_);
  scene_layers_[Foreground]->AttachChild(std::move(player));
}

// AdaptPlayerPosition checks the location origin of the command and current var
// The appropriate actions and boolean assignments are made to display
// in the level.
void Level::AdaptPlayerPosition(unsigned int location, int current_var) {
  switch (location) {
    case StartGadget:
      break;
    case Warp:
      if (!in_warp_gadget_) {
        mario_position_ = player_mario_->getPosition();
        if (current_var < 0) {
          mario_position_.x += 100;
          player_mario_->setPosition(mario_position_);
        } else {
          mario_position_.x += 200;
          player_mario_->setPosition(mario_position_);
        }
        in_warp_gadget_     = true;
        in_start_gadget_    = false;
        in_variable_gadget_ = false;
      }
      break;
    case VariableGadget:
      if (!in_variable_gadget_) {
        in_warp_gadget_ = false;
        mario_position_ = player_mario_->getPosition();
        std::cout << "MarPosy  : " << mario_position_.y << std::endl;
        sf::Vector2f variable_adjustment(110, 223);
        std::cout << "Current var abs: " << abs(current_var - 1) << std::endl;
        mario_position_.x  = 110;
        if (current_var > 2 ) {
          variable_adjustment.y = (variable_adjustment.y *
                                   abs(current_var - 1)) - 16; 
        }
        mario_position_.y  = variable_adjustment.y;
        std::cout << "After abs, MarPosy  : " << mario_position_.y << std::endl;
        player_mario_->setPosition(mario_position_);
        in_variable_gadget_ = true;
      }
      break;
    case Clause:
      break;
    case CheckIn:
      if (!in_check_in_) {
        in_variable_gadget_ = false;
        mario_position_ = player_mario_->getPosition();
        sf::Vector2f variable_adjustment(110, 215);
        mario_position_ += variable_adjustment;
        player_mario_->setPosition(mario_position_);
        in_check_in_ = true;
      }
      break;
    case CheckOut:
      break;
    case FinishGadget:
      break;
    default:
      std::cout << "WTF" << std::endl;
  }
}

void Level::HandleCollisions() {
  // if (player_mario_->)
  // unsigned int height  = tile_map_.GetTileMapHeight();
  // unsigned int width   = tile_map_.GetTileMapWidth();
  //
  // for (int i = 0; i < height; ++i) {
  //   for (int j = 0; j < width; ++j) {
  //     int current_tile = tile_map_.GetTileValue(i, j);
  //     sf::Vector2f tile_location(i * 16, j * 16);
  //     if (current_tile != 30 && ((mario_position_.x > tile_location.x))) {
  //       mario_position_.x = tile_l
  //
  //     }
  //   }
  // }
}

TileMap& Level::GetTileMap() {
  return tile_map_;
}

VariableManager Level::GetVarManager() {
  return zchaff_manager_.GetVarManager();
}
