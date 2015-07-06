// Copyright 2015, Aaron Ceross

#include <string>
#include <vector>
#include "../include/tile_map.hpp"

// Constructor and Destructor
TileMap::TileMap()  { initialiseMap(); }
TileMap::~TileMap() {}

// Loads in the map layout and graphical assets
// this function is addapted from the SFL tutorial on tilemaps
bool TileMap::loadMap(const std::string& tileset, sf::Vector2u tileSize) {
  if (!this->tileset.loadFromFile(tileset)) return false;

  // Resize the vertex array to fit the level size
  this->vertices.setPrimitiveType(sf::Quads);
  this->vertices.resize(width * height * 8);

  for (std::vector<std::vector<int>>::size_type i = 0; i < width; ++i) {
    for (std::vector<int>::size_type j = 0; j < height; ++j) {
      int tileNumber = i + j * width;
      int tileValue = t_map_[j][i].GetTileValue();

      printf("\n");
      printf("Tile Number = %d\n", tileNumber);
      printf("Tile Value = %d\n", tileValue);

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

// Prints the tilemap in the terminal
void TileMap::PrintMap() {
  for (std::vector<std::vector<int>>::size_type i = 0; i < t_map_.size(); ++i) {
    for (std::vector<int>::size_type j = 0; j < t_map_[i].size(); ++j) {
      std::cout << t_map_[i][j].GetTileValue() << ' ';
    }
    std::cout << std::endl;
  }
}

void TileMap::initialiseMap() {
  setParameters("assets/maps/map1.txt");
  PrintMap();
  loadMap("assets/gfx/level1.png", sf::Vector2u(32, 32));
}

void TileMap::resizeMap(int width, int height) {
  t_map_.resize(height);
  int check = t_map_.size();
  printf("Map resize is %d\n", check);
  for (unsigned int i = 0; i < height; ++i) {
    t_map_.resize(width);
  }
}

void TileMap::LoadBlocks() {
  for (unsigned int i = 0; i < height; ++i) {
    std::vector<Tile> tmp_value;
    for (unsigned int j = 0; j < width; ++j) {
      tmp_value.push_back(Tile());
    }
    t_map_.push_back(tmp_value);
  }
}

void TileMap::setParameters(std::string filepath) {
  std::ifstream mapfile(filepath);

  mapfile >> width >> height;

  LoadBlocks();

  int value;
  for (unsigned int i = 0; i < height; ++i) {
    std::vector<Tile> tmp_value;
    for (unsigned int j = 0; j < width; ++j) {
      mapfile >> value;
      printf("\n");
      printf("tilemap[%d][%d]", i, j);
      printf("Value = %d\n", value);
      t_map_[i][j].SetTileValue(value);
      // tmp_value.push_back(value);
      int p = t_map_[i][j].GetTileValue();
      printf("Value inserted: %d\n", p);
    }
    // t_map_.push_back(tmp_value);
  }
  printf("Map values successfully inserted!\n");
  mapfile.close();
}
