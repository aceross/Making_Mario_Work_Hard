// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <memory>

#include "../include/level.hpp"

Level::Level(sf::RenderTarget& output_target, FontHolder& fonts,
             MapfileHandler& mapfile_handler)
: target_(output_target)
, scene_texture_()
, level_view_(output_target.getDefaultView())
, textures_()
, fonts_(fonts)
, mapfile_handler_(mapfile_handler)
, mini_map_background_()
, scene_graph_()
, scene_layers_()
, level_bounds_(0.f, 0.f, level_view_.getSize().x, level_view_.getSize().y)
, mario_position_(0, 32)
, movement_speed_(2.5f)
, player_mario_(nullptr)
, koopa_list_()
, koopa_texture_()
, brick_list_()
, check_in_bricks_()
, zchaff_manager_()
, variable_manager_()
, level_complete_(false)
, display_solution(false)
, in_start_gadget_(false)
, in_variable_gadget_(false)
, in_warp_gadget_(false)
, warping_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
, current_clause_(0)
{
  scene_texture_.create(target_.getSize().x, target_.getSize().y);
  std::string mapfile = mapfile_handler_.GetMapfile();
  // Start and load SAT solver
  zchaff_manager_.LoadInstance(mapfile);
  variable_manager_ = zchaff_manager_.GetVarManager();

  // init level instance
  LoadTextures();
  BuildScene();

  // Prepare the main view and the mini-map
  level_view_.setCenter(player_mario_->getPosition());
  // level_view_.zoom(0.7f);
  mini_map_.setViewport(sf::FloatRect(0.72f, 0, 0.23f, 0.23f));
  mini_map_background_.setFillColor(sf::Color(0, 0, 0, 150));
  mini_map_background_.setSize(mini_map_.getSize());
}

void Level::Update(sf::Time delta_time) {
  if (!command_queue_.IsEmpty()) {
    Command c = command_queue_.Front();
    AdaptPlayerPosition(c.location_, c.var_assignment_,
                        c.current_clause_, c.has_action_);
    if (c.has_action_) {
      KickShell(c.var_assignment_, c.current_clause_, c.has_action_);
      SolveCheckIn();
    }
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
  target_.draw(flag_);

  if (!koopa_list_.empty()) {
    for (const sf::Sprite& koopa : koopa_list_) {
      target_.draw(koopa);
    }
  }
  for (const sf::Sprite& brick : brick_list_) {
    target_.draw(brick);
  }
  for (const sf::Sprite& brick : check_in_bricks_) {
    target_.draw(brick);
  }

  // draw the mini map view
  target_.setView(mini_map_);
  target_.draw(mini_map_background_);
  target_.draw(scene_graph_);
  target_.draw(tile_map_);
}

CommandQueue& Level::GetCommandQueue() {
  return command_queue_;
}

void Level::LoadTextures() {
  textures_.Load(Textures::Mario, "resources/gfx/mario_bros.png");
  koopa_texture_.loadFromFile("resources/gfx/enemies.png",
                               sf::IntRect(160, 81, 16, 16));
  brick_texture_.loadFromFile("resources/gfx/tile_set.png");
  flag_texture_.loadFromFile("resources/gfx/item_objects.png",
                              sf::IntRect(128, 32, 16, 16));
}

void Level::BuildScene() {
  // Initialise the different layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    Category::Type category = Category::None;
    SceneNode::Ptr layer(new SceneNode(category));
    scene_layers_[i] = layer.get();
    scene_graph_.AttachChild(std::move(layer));
  }

  // Add player sprite
  std::unique_ptr<Mario> player(new Mario(Mario::SmallMario, textures_, fonts_));
  player_mario_ = player.get();
  player_mario_->setPosition(mario_position_);
  scene_layers_[Foreground]->AttachChild(std::move(player));

  // Read in the tile map
  tile_map_.InitialiseMap(zchaff_manager_);
  std::unique_ptr<MapNode> map_node(new MapNode());
  map_node->tile_map_.InitialiseMap(zchaff_manager_);
  scene_layers_[Background]->AttachChild(std::move(map_node));

  // Add world Objects
  AddWorldObjects();
}

void Level::AddWorldObjects() {
  int cl   = variable_manager_.GetNumClauses();
  int vars = variable_manager_.GetNumVariables();

  // Add end flag
  flag_.setTexture(flag_texture_);

  // Clause gadgets(27 tiles) + CheckIn(8 tiles) + Position in finish(11 tiles)
  //
  int flag_x = (cl * (TILE_SIZE * 27)) + (TILE_SIZE * 8) + (TILE_SIZE * 11) +
                6 + (TILE_SIZE * (cl-1));
  int flag_y = (vars * (TILE_SIZE * 13)) + (TILE_SIZE * 10) + 13;
  flag_.setPosition(flag_x, flag_y);

  // Add Koopa Shells
  for (int i = 0; i < vars; ++i) {
    for (int j = 0; j < cl; ++j) {
      sf::Sprite koopa;
      koopa.setTexture(koopa_texture_);
      sf::Vector2f koopa_position(160, (208  * vars) + (TILE_SIZE * 4));
      koopa_position.x += ((432 * j) + (TILE_SIZE * j));
      koopa_position.x += (9 * i) * TILE_SIZE;
      koopa.setPosition(koopa_position);
      koopa_list_.push_back(koopa);
    }
  }

  /* Add Bricks
  ----------------------------------------------------------------------------*/
  // Set replacement blank brick
  blank_brick_.setTexture(brick_texture_);
  blank_brick_.setTextureRect(sf::IntRect(436, 136, 16, 16));

  // brick blocking the small passage
  for (int k = 0; k < cl; ++k) {
    sf::Sprite brick;
    brick.setTexture(brick_texture_);
    brick.setTextureRect(sf::IntRect(16, 0, 16, 16));
    sf::Vector2f clause_brick_position(208, (208  * vars) + (TILE_SIZE * 13));
    clause_brick_position.x += ((432 * k) + (TILE_SIZE * k));
    brick.setPosition(clause_brick_position);
    brick_list_.push_back(brick);
  }

  // check in brick
  sf::Sprite check_in_brick;
  check_in_brick.setTexture(brick_texture_);
  check_in_brick.setTextureRect(sf::IntRect(16, 0, 16, 16));
  sf::Vector2f check_in_position(32, (208  * vars) + (TILE_SIZE * 13));
  check_in_brick.setPosition(check_in_position);
  check_in_bricks_.push_back(check_in_brick);

  // final brick
  sf::Sprite final_brick;
  final_brick.setTexture(brick_texture_);
  final_brick.setTextureRect(sf::IntRect(16, 0, 16, 16));
  sf::Vector2f final_position((432 * cl) + 224 + (TILE_SIZE * cl),
                              (208  * vars) + (TILE_SIZE * 15));
  final_brick.setPosition(final_position);
  check_in_bricks_.push_back(final_brick);
}

void Level::SolveCheckIn() {
  if (in_check_in_) {
    check_in_bricks_[0] = blank_brick_;
  }
  if (in_finish_) {
    check_in_bricks_[1] = blank_brick_;
  }
}

void Level::KickShell(int current_clause, int current_var, bool has_action) {
  if (in_clause_gadget_ && has_action) {
    int num_vars = variable_manager_.GetNumVariables();
    std::cout << "Current Var" << current_var << std::endl;
    std::cout << "Current CL" << current_clause << std::endl;
    int position = ((abs(current_clause) - 1) * (num_vars)) + current_var;
    std::cout << "Kick Position : " << position << std::endl;
    koopa_list_[position]    = blank_brick_;
    brick_list_[current_var] = blank_brick_;
  }
}

// AdaptPlayerPosition checks the location origin of the command and current var
// The appropriate actions and boolean assignments are made to display
// in the level.
void Level::AdaptPlayerPosition(unsigned int location, int current_var,
                                int current_clause, bool has_action) {
  switch (location) {
    case StartGadget:
      break;
    case WarpEntry:
      if (!in_warp_gadget_) {
        int cl = variable_manager_.GetNumClauses();
        int variable_adjustment(16);
        mario_position_ = player_mario_->getPosition();
        if (current_var < 0) {
          mario_position_.x += (15 + (cl * 3)) * TILE_SIZE;
        } else {
          // 192 from 12 * 16
          mario_position_.x += 192;
        }
        if (current_var > 1) {
          mario_position_.y -= (variable_adjustment * abs(current_var)) -
                               (16 * (abs(current_var) - 2));
        } else {
            mario_position_.y -= (variable_adjustment * abs(current_var));
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
        mario_position_   = player_mario_->getPosition();
        sf::Vector2f variable_adjustment(110, 223);
        mario_position_.x  = 110;
        if (abs(current_var) > 1 ) {
          // Subtract one from current_var because the Start Gadget counts
          // as one variable.
          variable_adjustment.y = (floor(variable_adjustment.y *
                                   (abs(current_var) - 1))) -
                                   (TILE_SIZE * ((abs(current_var)-2)));
        }
        mario_position_.y  = variable_adjustment.y;
        player_mario_->setPosition(mario_position_);
        in_variable_gadget_ = true;
      }
      break;
    case Clause:
      if (!in_clause_gadget_) {
        return_position_  = player_mario_->getPosition();
        in_clause_gadget_ = true;
        current_clause_   = current_clause;
        int vars          = variable_manager_.GetNumVariables();
        // Var gadgets are 14 tiles across; 14 * 16 = 208
        // Multiply by amounts of variables to get to gadget clause on y-axis
        sf::Vector2f clause_adjustment(0, (208  * vars));
        // the tiles are 14 to the first landing point multiple by TIlE_SIZE
        // for the next clause add 432 -- > 27 (width of clause) * 16
        // adjust when moving to next clause -> add 16 * current clause
        clause_adjustment.x += 224 + ((432 * current_clause_) +
                                      (TILE_SIZE * current_clause_));
        // adjust for variable location
        // the ledges are 9 tiles away from each other
        // Multiply by (var - 1), as first one is done and adjust by TILE_SIZE
        clause_adjustment.x += (9 * (abs(current_var) - 1)) * TILE_SIZE;
        clause_adjustment.y  = clause_adjustment.y + (TILE_SIZE * 3);
        player_mario_->setPosition(clause_adjustment);
      } else if (in_clause_gadget_ && has_action) {
        std::cout << "Kick" << std::endl;
      } else {
        player_mario_->setPosition(return_position_);
        in_clause_gadget_ = false;
      }
      break;
    case CheckIn:
      if (!in_check_in_) {
        int vars            = variable_manager_.GetNumVariables();
        in_variable_gadget_ = false;
        mario_position_     = player_mario_->getPosition();
        sf::Vector2f check_in_adjustment(TILE_SIZE * 2,
                                        (208  * vars) + 15 * TILE_SIZE);
        player_mario_->setPosition(check_in_adjustment);
        in_check_in_ = true;
      }
      break;
    case CheckOut:
      break;
    case FinishGadget:
      in_finish_ = true;
      break;
    default:
      std::cout << "Something has gone incredibly wrong" << std::endl;
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
