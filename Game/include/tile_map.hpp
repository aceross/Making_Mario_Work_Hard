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
#include "tile.hpp"

class TileMap : public sf::Sprite {
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
  std::vector<std::vector<Tile>> t_map_;

  unsigned int height;
  unsigned int width;

 private:
  // For collision
  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;

  void LoadBlocks();
  void setParameters(std::string filepath);
  void resizeMap(int width, int height);
  void PrintMap();
};

#endif  // TILE_MAP_HPP
