// Copyright 2015, Aaron Ceross

#ifndef NAVIGATION_MANAGER_HPP
#define NAVIGATION_MANAGER_HPP

// #include "../include/map_chunk_manager.hpp"
#include "../include/tile_map.hpp"
#include "../include/command_queue.hpp"

class NavigationManager {
 public:
  NavigationManager();
  NavigationManager(TileMap tm);
  void InitialiseQueues();
  void GetTileMap(TileMap tm);
 private:
  // MapChunkManager chunk_manager_;
  TileMap tile_map_;

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
