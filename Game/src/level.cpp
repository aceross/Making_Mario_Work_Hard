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
, warping_(false)
, finished_warps_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
, current_clause_(0)
{
  scene_texture_.create(target_.getSize().x, target_.getSize().y);

  // Start and load SAT solver
  zchaff_manager_.LoadInstance();
  variable_manager_ = zchaff_manager_.GetVarManager();

  // init level instance
  LoadTextures();
  BuildScene();

  // Prepare the main view and the mini-map
  level_view_.setCenter(player_mario_->getPosition());
  // level_view_.zoom(0.57f);
  mini_map_.setViewport(sf::FloatRect(0.72f, 0, 0.23f, 0.23f));
}

void Level::Update(sf::Time delta_time) {
  if (!command_queue_.IsEmpty()) {
    Command c = command_queue_.Front();
    AdaptPlayerPosition(c.location_, c.var_assignment_, c.current_clause_);
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
  target_.draw(tile_map_);
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
void Level::AdaptPlayerPosition(unsigned int location, int current_var,
                                int current_clause) {
  switch (location) {
    case StartGadget:
      break;
    case WarpEntry:
      if (!in_warp_gadget_) {
        int variable_adjustment(16);
        mario_position_ = player_mario_->getPosition();
        if (current_var < 0) {
          mario_position_.x += 380;
          mario_position_.y -= variable_adjustment * abs(current_var - 1) - 16;
        } else {
          mario_position_.x += 192;
          if (current_var > 1) {
            mario_position_.y -= variable_adjustment * abs(current_var) - 16;
          } else {
            mario_position_.y -= variable_adjustment * abs(current_var);
          }
        }
        player_mario_->setPosition(mario_position_);
        in_warp_gadget_     = true;
        in_start_gadget_    = false;
        in_variable_gadget_ = false;
      }
      break;
    case Warp:
      break;
    case WarpExit:
      break;
    case VariableGadget:
      if (!in_variable_gadget_) {
        in_warp_gadget_   = false;
        in_clause_gadget_ = false;
        mario_position_ = player_mario_->getPosition();
        sf::Vector2f variable_adjustment(110, 223);
        mario_position_.x  = 110;
        if (abs(current_var) > 2 ) {
          // Subtract one from current_var because the Start Gadget counts
          // as one variable.
          variable_adjustment.y = floor(variable_adjustment.y *
                                   abs(current_var - 1) - 16) + 1;
        }
        mario_position_.y  = variable_adjustment.y;
        player_mario_->setPosition(mario_position_);
        in_variable_gadget_ = true;
      }
      break;
    // TIMES 8 NOT 16 !!!!!
    case Clause:
      if (!in_clause_gadget_) {
        return_position_  = player_mario_->getPosition();
        in_clause_gadget_ = true;
        current_clause_   = current_clause;
        int vars          = variable_manager_.GetNumVariables();
        sf::Vector2f clause_adjustment(0, 104 * (vars - 1));
        // the tiles are 14 to the first landing point multiple by TIlE_SIZE
        // for the next clause add 432 -- > 27 (width of clause) * 16
        // adjust when moving to next clause -> add 16 * current clause
        clause_adjustment.x += 224 + ((432 * current_clause_) +
                                      (TILE_SIZE * current_clause_));
        // adjust for variable location
        clause_adjustment.x += (9 * (abs(current_var) - 1)) * TILE_SIZE;

        std::cout << "Current var:   " << abs(current_var) << ": " << clause_adjustment.x << std::endl;
        clause_adjustment.y = clause_adjustment.y * (vars) + (TILE_SIZE * vars);
        player_mario_->setPosition(clause_adjustment);
      } else {
        player_mario_->setPosition(return_position_);
        in_clause_gadget_ = false;
      }
      break;
    case CheckIn:
      if (!in_check_in_) {
        in_variable_gadget_ = false;
        mario_position_ = player_mario_->getPosition();
        sf::Vector2f check_in_adjustment(110, 215);
        mario_position_ += check_in_adjustment;
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

int Level::GetClauseLocation(int current_var) {
  int num_clauses = variable_manager_.GetNumClauses();
  int num_vars    = variable_manager_.GetNumVariables();
  int clause;
  for (int i = 0; i < num_clauses; ++i) {
    for (int j = 0; j < num_vars; ++j) {
      int literal = variable_manager_.clauses_[i][j];
      if (current_var == literal && current_clause_ < num_clauses) {
        // std::cout << "Current Literal : "  << literal << std::endl;
        // std::cout << "Current Clause  : "  << i + 1 << std::endl;
        clause = i + 1;
        break;
      }
    }
  }
  return clause;
}

void Level::HandleCollisions() {}

TileMap& Level::GetTileMap() {
  return tile_map_;
}

VariableManager Level::GetVarManager() {
  return zchaff_manager_.GetVarManager();
}
