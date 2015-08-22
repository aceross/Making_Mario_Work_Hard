// Copyright 2015, Aaron Ceross

#ifndef MAP_CHUNK_MANAGER_HPP
#define MAP_CHUNK_MANAGER_HPP

#include <string>
#include "map_chunk.hpp"

class MapChunkManager {
 public:
  MapChunkManager();
  void InitialiseMapChunks();

 private:
  void InitStartGadget();
  void InitVariableChunk();
  void InitWarpPipe();
  void InitWarpStart();
  void InitWarpEnd();
  void InitCheckIn();
  void InitClause();
  void InitFinishGadget();

 public:
  MapChunk start_gadget_;
  MapChunk variable_gadget_;
  MapChunk warp_pipe_;
  MapChunk warp_start_;
  MapChunk warp_end_;
  MapChunk check_in_;
  MapChunk clause_;
  MapChunk finish_gadget_;
};

#endif  // MAP_GENERATION_MANAGER_HPP
