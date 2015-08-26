// Copyright 2015, Aaron Ceross

#include "../include/navigation_manager.hpp"


NavigationManager::NavigationManager(MapChunkManager cm, TileMap tm)
: in_start_gadget_(false)
, in_variable_gadget_(false)
, in_warp_gadget_(false)
, in_check_in_(false)
, in_clause_gadget_(false)
, in_check_out_(false)
, in_finish_(false)
{
  chunk_manager_ = cm;
  tile_map_      = tm;
}
