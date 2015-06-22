// Copyright 2015, Aaron Ceross

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>

#include "level.hpp"

class TileMap {
 public:
  TileMap();
  ~TileMap();
  bool loadMap(const std::string& tileset, sf::Vector2u tileSize,
               const int* tiles, unsigned int width, unsigned int height);
  void setTiles();
  void initialiseMap();
  // void draw();
  // Level level;
  sf::VertexArray vertices;
  sf::Texture     tileset;
  sf::Sprite      tiles;
 private:
  void setParameters(std::string filepath);
  void resizeMap(int width, int height);
  void printMap();
  unsigned int height;
  unsigned int width;
  std::vector<std::vector<int>> map;
};

#endif  // TILE_MAP_HPP
