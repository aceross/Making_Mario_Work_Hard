// Copyright 2015, Aaron Ceross

#include <string>
#include <vector>
# include "../../include/tile_map.hpp"

TileMap::TileMap()  {}

TileMap::~TileMap() {}

void TileMap::CreateChunkMap(unsigned int var, unsigned int clause) {
  test_map_.clear();
  std::vector<std::string> innerstart;
  innerstart.push_back("start_gadget");
  for (int i = 0; i < 2; ++i) {
    innerstart.push_back("warp_start");
    for (int i = 0; i < clause; ++i) {
      innerstart.push_back("warp");
    }
    innerstart.push_back("warp_end");
  }

  std::vector<std::string> innervar;
  innervar.push_back("variable_gadget");
  for (int i = 0; i < 2; ++i) {
    innervar.push_back("warp_start");
    for (int i = 0; i < clause; ++i) {
      innervar.push_back("warp");
    }
    innervar.push_back("warp_end");
  }

  std::vector<std::string> innerend;
  innerend.push_back("check_in");
  for (int m = 0; m < clause; ++m) {
    innerend.push_back("clause_gadget");
  }
  innerend.push_back("finish_gadget");

  test_map_.push_back(innerstart);
  for (int i = 0; i < var - 1; ++i) {
    test_map_.push_back(innervar);
  }

  test_map_.push_back(innerend);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &tileset_;

  // draw the vertex array
  target.draw(vertices_, states);
}
