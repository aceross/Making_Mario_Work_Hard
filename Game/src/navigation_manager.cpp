// Copyright 2015, Aaron Ceross

#include "../include/navigation_manager.hpp"

NavigationManager::NavigationManager()
: right_move_(sf::Vector2f(30, 0))
, left_move_(sf::Vector2f(-16, 0))
, jump_move_(sf::Vector2f(0, -16))
, fall_move_(sf::Vector2f(0, 16))
, in_start_gadget_(false)
, in_variable_gadget_(false)
, in_warp_gadget_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
, in_finish_(false)
{
  std::cout << "Navigation manager set" << std::endl;
  InitialiseQueues();
}

void NavigationManager::GetTileMap(TileMap tm) {
  tile_map_ = tm;
}

void NavigationManager::InitialiseQueues() {
  InitStartQueue();
  // InitVariableQueue();
  // InitWarpQueue();
  // InitClauseQueue();
  // InitCheckInQueue();
  // InitCheckoutQueue();
  // InitFinishQueue();
  std::cout << "Queues Initialised" << std::endl;
  solution_queue_.push_back(start_gadget_actions_);
  std::cout << "Start Gadget Actions added" << std::endl;
}

void NavigationManager::InitStartQueue() {
  for (int i = 0; i < 10; ++i) {
    start_gadget_actions_.push(right_move_);
  }
  start_gadget_actions_.push(jump_move_);
}
