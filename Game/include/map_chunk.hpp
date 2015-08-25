// Copyright 2015, Aaron Ceross

#ifndef MAP_CHUNK_HPP
#define MAP_CHUNK_HPP

#include <string>

class MapChunk {
 public:
  MapChunk();
  std::string name_;
  std::string file_path_;
  unsigned int chunk_height_;
  unsigned int chunk_width_;
};

#endif  // MAP_CHUNK_HPP
