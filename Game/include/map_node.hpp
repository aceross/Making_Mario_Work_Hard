// Copyright 2015, Aaron Ceross

#ifndef MAP_NODE_HPP
#define MAP_NODE_HPP

#include "tmx/MapLoader.h"
#include "scene_node.hpp"

class MapNode : public SceneNode {
 public:
  MapNode();

 private:
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

 public:
  tmx::MapLoader ml_;
};

#endif  // MAP_NODE_HPP
