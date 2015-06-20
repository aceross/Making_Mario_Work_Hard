// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/tile_map.hpp"

// Constructor and Destructor
TileMap::TileMap()  {}
TileMap::~TileMap() {}

void TileMap::loadMap() {
  std::ifstream openfile("assets/maps/map1.txt");

  sf::Vector2i map[100][100];
  sf::Vector2i loadCounter = sf::Vector2i(0, 0);

  if ( openfile.is_open() ) {
    std::string tile_location;
    openfile >> tile_location;
    this->tile_Texture.loadFromFile(tile_location);
    this->tiles.setTexture(this->tile_Texture);

    while ( !openfile.eof() ) {
      std::string str;
      openfile >> str;
      char x = str[0], y = str[2];

      if ( !isdigit(x) || !isdigit(y) ) {
        map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
      } else {
        map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
      }

      if ( openfile.peek() == '\n' ) {
        loadCounter.x = 0;
        loadCounter.y++;
      } else { loadCounter.x++; }
    }
  }
}
