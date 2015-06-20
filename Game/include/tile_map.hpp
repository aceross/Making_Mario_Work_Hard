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
  void loadMap();
  void setTiles();

  sf::Texture tile_Texture;
  sf::Sprite  tiles;
 private:
  sf::Vector2i map[100][100];
  sf::Vector2i loadCounter = sf::Vector2i(0, 0);
};

#endif  // TILE_MAP_HPP
