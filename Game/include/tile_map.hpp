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

class TileMap : public sf::Drawable, public sf::Transformable {
 public:
  using sf::Drawable::draw;
  TileMap();
  ~TileMap();
  bool loadMap(const std::string& tileset, sf::Vector2u tileSize);
  void initialiseMap();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::VertexArray vertices;
  sf::Texture     tileset;
  sf::Sprite      tiles;
  std::vector<std::vector<int>> map;
 private:
  void setParameters(std::string filepath);
  void resizeMap(int width, int height);
  void printMap();
  unsigned int height;
  unsigned int width;
};

#endif  // TILE_MAP_HPP
