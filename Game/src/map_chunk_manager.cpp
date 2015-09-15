// Copyright 2015, Aaron Ceross

#include "../include/map_chunk_manager.hpp"

MapChunkManager::MapChunkManager() {}

// Adds the map chunk values to the manager.
// These values must be changed if a new sort of map is required.
// Ensure that map values match those found in the relative files.
void MapChunkManager::InitialiseMapChunks() {
  InitStartGadget();
  InitWarpStart();
  InitWarpPipe();
  InitWarpEnd();
  InitVariableChunk();
  InitCheckIn();
  InitClause();
  InitFinishGadget();
}

void MapChunkManager::InitStartGadget() {
  start_gadget_.name_         = "start_gadget";
  start_gadget_.file_path_    = "resources/maps/level_chunks/start_chunk.map";
  start_gadget_.chunk_height_ = 13;
  start_gadget_.chunk_width_  = 21;
}

void MapChunkManager::InitWarpStart() {
  warp_start_.name_         = "warp_start";
  warp_start_.file_path_    = "resources/maps/level_chunks/start_warp_chunk.map";
  warp_start_.chunk_height_ = 13;
  warp_start_.chunk_width_  = 5;
}

void MapChunkManager::InitWarpPipe() {
  warp_pipe_.name_         = "warp";
  warp_pipe_.file_path_    = "resources/maps/level_chunks/warp.map";
  warp_pipe_.chunk_height_ = 13;
  warp_pipe_.chunk_width_  = 3;
}

void MapChunkManager::InitWarpEnd() {
  warp_end_.name_         = "warp_end";
  warp_end_.file_path_    = "resources/maps/level_chunks/exit_warp_chunk.map";
  warp_end_.chunk_height_ = 13;
  warp_end_.chunk_width_  = 4;
}

void MapChunkManager::InitVariableChunk() {
  variable_gadget_.name_         = "variable_gadget";
  variable_gadget_.file_path_    = "resources/maps/level_chunks/variable_gadget.map";
  variable_gadget_.chunk_height_ = 13;
  variable_gadget_.chunk_width_  = 21;
}

void MapChunkManager::InitCheckIn() {
  check_in_.name_         = "check_in";
  check_in_.file_path_    = "resources/maps/level_chunks/check_in_gadget.map";
  check_in_.chunk_height_ = 19;
  check_in_.chunk_width_  = 8;
}

void MapChunkManager::InitClause() {
  clause_.name_         = "clause_gadget";
  clause_.file_path_    = "resources/maps/level_chunks/clause.map";
  clause_.chunk_height_ = 19;
  clause_.chunk_width_  = 28;
}

void MapChunkManager::InitFinishGadget() {
  finish_gadget_.name_         = "finish_gadget";
  finish_gadget_.file_path_    = "resources/maps/level_chunks/finish_gadget.map";
  finish_gadget_.chunk_height_ = 19;
  finish_gadget_.chunk_width_  = 21;
}
