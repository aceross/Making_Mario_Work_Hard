// Copyright 2015, Aaron Ceross

#ifndef NAVIGATION_MANAGER_HPP
#define NAVIGATION_MANAGER_HPP

#include <vector>

// #include "../include/map_chunk_manager.hpp"
#include "../include/tile_map.hpp"
#include "../include/command_queue.hpp"

class NavigationManager {
 public:
  NavigationManager();

  void GetTileMap(TileMap tm);
  void InitialiseAction();
  void InitialiseQueues();

  void InitStartQueue();
  void InitVariableQueue();
  void InitWarpQueue();
  void InitClauseQueue();
  void InitCheckInQueue();
  void InitCheckoutQueue();
  void InitFinishQueue();

  // std::vector<std::queue< sf::Vector2f > > solution_queue_;
  // std::queue<sf::Vector2f> start_gadget_actions_;
 private:
  TileMap tile_map_;
  int current_variable_;
  unsigned int current_clause_;

private:
  sf::Vector2f right_move_;
  sf::Vector2f left_move_;
  sf::Vector2f jump_move_;
  sf::Vector2f fall_move_;

 private:
  CommandQueue start_gadget_actions_;
  // std::queue<actions> variable_gadget_actions_;
  // std::queue<actions> warp_gadget_actions_;
  // std::queue<actions> clause_gadget_actions_;
  // std::queue<actions> checkin_gadget_actions_;
  // std::queue<actions> checkout_gadget_actions_;
  // std::queue<actions> finish_gadget_actions_;

private:
  // location boolean values
  bool in_start_gadget_;
  bool in_variable_gadget_;
  bool in_warp_gadget_;
  bool in_check_in_;
  bool in_clause_gadget_;
  bool in_check_out_;
  bool in_finish_;
};

#endif  // NAVIGATION_MANAGER_HPP
