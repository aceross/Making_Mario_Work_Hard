// Copyright 2015, Aaron Ceross

#ifndef MAP_NODE_HPP
#define MAP_NODE_HPP

#include "scene_node.hpp"
#include "tile_map.hpp"

class MapNode : public SceneNode {
 public:
  MapNode();

 private:
  void GenerateMap();
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

 public:
  TileMap tile_map_;

};

#endif  // MAP_NODE_HPP
