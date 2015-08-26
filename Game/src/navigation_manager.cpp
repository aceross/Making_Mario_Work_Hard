// Copyright 2015, Aaron Ceross

#include "../include/navigation_manager.hpp"

NavigationManager::NavigationManager()
: in_start_gadget_(false)
, in_variable_gadget_(false)
, in_warp_gadget_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
, in_finish_(false)
{
}

NavigationManager::NavigationManager(TileMap tm)
: in_start_gadget_(false)
, in_variable_gadget_(false)
, in_warp_gadget_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
, in_finish_(false)
{
  // chunk_manager_ = tm.chunk_map_;
  tile_map_ = tm;
  // chunk_manager_ = tile_map_.chunk_map_;
  std::cout << "Navigation manager set" << std::endl;
}

void NavigationManager::GetTileMap(TileMap tm) {
  tile_map_ = tm;
}

void NavigationManager::InitialiseQueues() {

}
