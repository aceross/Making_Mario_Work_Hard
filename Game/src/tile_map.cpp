// Copyright 2015, Aaron Ceross

#include <string>
#include <vector>
#include "../include/tile_map.hpp"

// Constructor and Destructor
TileMap::TileMap()  { initialiseMap(); }
TileMap::~TileMap() {}

// loads in the map layout and graphical assets
bool TileMap::loadMap(const std::string& tileset, sf::Vector2u tileSize) {
  // Load the tileset texture
  if (!this->tileset.loadFromFile(tileset)) return false;

  // Resize the vertex array to fit the level size
  this->vertices.setPrimitiveType(sf::Quads);
  this->vertices.resize(width * height * 8);

  int mapsize = map.size();
  printf("Map size is %d\n", mapsize);

  for (std::vector<std::vector<int>>::size_type i = 0; i < map.size(); ++i) {
    for (std::vector<int>::size_type j = 0; j < map[i].size(); ++j) {
      int tileNumber = i + j * width;
      int tileValue = map[i][j];
      int mapsize_2 = map[i].size();

      printf("\n");
      printf("Tile Number = %d\n", tileNumber);
      printf("Tile Value = %d\n", tileValue);
      printf("Map size 2 is %d\n", mapsize_2);

      // Find the tileValue's position in the tileset texture
      // 'tu' is the column value on the tileset
      // 'tv' is the row value on the tileset
      int tu = tileValue % (this->tileset.getSize().x / tileSize.x);
      int tv = tileValue / (this->tileset.getSize().x / tileSize.x);

      printf("Coordinates map [%lu][%lu]\n", i, j);
      printf("TU = %d\n", tu);
      printf("TV = %d\n", tv);

      // Get a pointer to the current tile's quad
      sf::Vertex* quad = &vertices[(i + j * width) * 4];

      // define the current tile's four corners
      quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x,
                                      (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      // define the current tile's four texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x,
                                       (tv + 1) * tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
  }
  return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &tileset;

  // draw the vertex array
  target.draw(vertices, states);
}

void TileMap::printMap() {
  for (std::vector<std::vector<int>>::size_type i = 0; i < map.size(); ++i) {
    for (std::vector<int>::size_type j = 0; j < map[i].size(); ++j) {
      std::cout << map[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

void TileMap::setTiles() {
  // for (int i = 0; i < loadCounter.x; ++i) {
  //   for (int j = 0; j < loadCounter.y; ++j) {
  //     if (map[i][j].x != -1 && map[i][j].y != -1) {
  //       tiles.setPosition(i = 32, j = 32);
  //       tiles.setTextureRect(sf::IntRect(map[i][j].x * 32,
  //                            map[i][j].y * 32, 32, 32));
  //     }
  //   }
  // }
}

void TileMap::initialiseMap() {
  setParameters("assets/maps/map1.txt");
  printMap();
  loadMap("assets/gfx/tileset.png", sf::Vector2u(32, 32));
}

void TileMap::resizeMap(int width, int height) {
  map.resize(height);
  int check = map.size();
  printf("Map resize is %d\n", check);
  for (unsigned int i = 0; i < height; ++i) {
    map.resize(width);
  }
}

void TileMap::setParameters(std::string filepath) {
  std::ifstream mapfile(filepath);

  mapfile >> width >> height;

  int value;
  // resizeMap(width, height);
  for (unsigned int i = 0; i < height; ++i) {
    std::vector<int> tmp_value;
    for (unsigned int j = 0; j < width; ++j) {
      mapfile >> value;
      tmp_value.push_back(value);
    }
    map.push_back(tmp_value);
  }
  printf("Map values successfully inserted!\n");
  mapfile.close();
}
