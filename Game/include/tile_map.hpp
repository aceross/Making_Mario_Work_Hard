// Copyright 2015, Aaron Ceross

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>

class TileMap {
 public:
  TileMap();
  ~TileMap();
 private:
  sf::Texture tile_Texture;
  sf::Sprite tiles;
  void loadMap();
};

#endif  // TILE_MAP_HPP
