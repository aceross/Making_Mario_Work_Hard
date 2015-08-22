// Copyright 2015, Aaron Ceross

#include <string>
#include <vector>
#include "../include/tile_map.hpp"

TileMap::TileMap()  {
  map_chunk_manager_.InitialiseMapChunks();
}

TileMap::~TileMap() {}

// Loads in the map layout and graphical assets
// this function is addapted from the SFL tutorial on tilemaps
bool TileMap::LoadMap(const std::string& tileset, sf::Vector2u tile_size) {
  if (!tileset_.loadFromFile(tileset)) return false;

  // Resize the vertex array to fit the level size
  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(width_ * height_ * 8);

  for (std::vector<std::vector<int>>::size_type i = 0; i < width_; ++i) {
    for (std::vector<int>::size_type j = 0; j < height_; ++j) {
      int tile_number = i + j * width_;
      int tile_value = t_map_[j][i].GetTileValue();

      t_map_[j][i].SetTileID(tile_number);

      // Find the tileValue's position in the tileset texture
      // 'tu' is the column value on the tileset
      // 'tv' is the row value on the tileset
      int tu = tile_value % (tileset_.getSize().x / tile_size.x);
      int tv = tile_value / (tileset_.getSize().x / tile_size.x);

      // Get a pointer to the current tile's quad
      sf::Vertex* quad = &vertices_[(i + j * width_) * 4];

      // define the current tile's four corners
      quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size.x,
                                      (j + 1) * tile_size.y);
      quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

      t_map_[j][i].SetTilePosition(quad[0].position);

      // define the current tile's four texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x,
                                       (tv + 1) * tile_size.y);
      quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
    }
  }
  return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &tileset_;

  // draw the vertex array
  target.draw(vertices_, states);
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

void TileMap::InitialiseMap(ZChaffManager zchaff_manager) {
  // SetParameters("resources/maps/level.map");
  // PrintMap();
  SetSATParameters(zchaff_manager);
  if (!LoadMap("resources/gfx/tile_set.png", sf::Vector2u(16, 16))) {
    std::cerr << "Error loading map graphics" << std::endl;
  }
}

void TileMap::SetSATParameters(ZChaffManager zchaff_manager) {
  num_clauses_     = zchaff_manager.GetNumClauses();
  num_variables_   = zchaff_manager.GetNumVariables();
  num_warp_gadgets = num_variables_ * 2;

  AddStartGadget();
}

void TileMap::AddStartGadget() {
  std::cout << "Chunk Height" << map_chunk_manager_.start_gadget_.chunk_height_ << std::endl;
  std::cout << "Chunk Width" << map_chunk_manager_.start_gadget_.chunk_width_ << std::endl;

  height_ = map_chunk_manager_.start_gadget_.chunk_height_;
  width_  = map_chunk_manager_.start_gadget_.chunk_width_;

  std::cout << "height = " << height_ << std::endl;
  std::cout << "width = "  << width_  << std::endl;

  ChunkReader(map_chunk_manager_.start_gadget_);
}

void TileMap::ChunkReader(MapChunk chunk) {
  std::ifstream chunk_file(chunk.file_path_);
  for (unsigned int i = 0; i < chunk.chunk_height_; ++i) {
    std::vector<Tile> tmp_value;
    for (unsigned int j = 0; j < chunk.chunk_width_; ++j) {
      tmp_value.push_back(Tile());
    }
    t_map_.push_back(tmp_value);
  }
  std::cout << "Added Tiles" << std::endl;
  int value;
  for (unsigned int i = 0; i < height_; ++i) {
    for (unsigned int j = 0; j < width_; ++j) {
      chunk_file >> value;
      std::cout << value << std::endl;
      t_map_[i][j].SetTileValue(value);
    }
  }
  std::cout << "Added Tile values" << std::endl;
}


void TileMap::ResizeMap(int width, int height) {
  t_map_.resize(height);
  int check = t_map_.size();
  printf("Map resize is %d\n", check);
  for (unsigned int i = 0; i < height; ++i) {
    t_map_.resize(width);
  }
}

void TileMap::LoadTileObjects() {
  for (unsigned int i = 0; i < height_; ++i) {
    std::vector<Tile> tmp_value;
    for (unsigned int j = 0; j < width_; ++j) {
      tmp_value.push_back(Tile());
    }
    t_map_.push_back(tmp_value);
  }
}

void TileMap::SetParameters(std::string filepath) {
  std::ifstream mapfile(filepath);

  mapfile >> width_ >> height_;

  LoadTileObjects();

  int value;
  for (unsigned int i = 0; i < height_; ++i) {
    for (unsigned int j = 0; j < width_; ++j) {
      mapfile >> value;
      t_map_[i][j].SetTileValue(value);
    }
  }
  printf("Map values successfully inserted!\n");
  mapfile.close();
}
