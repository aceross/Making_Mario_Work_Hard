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

#include "tile.hpp"

class TileMap : public sf::Sprite {
 public:
  using sf::Drawable::draw;
  TileMap();
  ~TileMap();
  bool LoadMap(const std::string& tileset, sf::Vector2u tileSize);
  void InitialiseMap();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::VertexArray vertices_;
  sf::Texture     tileset_;
  sf::Sprite      tiles_;
  std::vector<std::vector<Tile> > t_map_;

  unsigned int height;
  unsigned int width;

 private:
  // For collision
  sf::FloatRect GetLocalBounds() const;
  sf::FloatRect GetGlobalBounds() const;

  void LoadBlocks();
  void SetParameters(std::string filepath);
  void ResizeMap(int width, int height);
  void PrintMap();
};

#endif  // TILE_MAP_HPP
