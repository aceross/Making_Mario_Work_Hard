// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/tile_map.hpp"

TileMap::TileMap()  {
  map_chunk_manager_.InitialiseMapChunks();
}

TileMap::~TileMap() {}

// Loads in the map layout and graphical assets
// this function is addapted from the SFML tutorial on tilemapss
bool TileMap::LoadMap(const std::string& tileset, sf::Vector2u tile_size) {
  if (!tileset_.loadFromFile(tileset)) return false;

  // Resize the vertex array to fit the level size
  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(tilemap_width_ * tilemap_height_ * 8);

  for (std::vector<std::vector<int>>::size_type i = 0; i < tilemap_width_; ++i) {
    for (std::vector<int>::size_type j = 0; j < tilemap_height_; ++j) {
      int tile_number = i + j * tilemap_width_;
      int tile_value = t_map_[j][i].GetTileValue();

      t_map_[j][i].SetTileID(tile_number);

      // Find the tileValue's position in the tileset texture
      // 'tu' is the column value on the tileset
      // 'tv' is the row value on the tileset
      int tu = tile_value % (tileset_.getSize().x / tile_size.x);
      int tv = tile_value / (tileset_.getSize().x / tile_size.x);

      // Get a pointer to the current tile's quad
      sf::Vertex* quad = &vertices_[(i + j * tilemap_width_) * 4];

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
  ChunkToTileMap();

  if (!LoadMap("resources/gfx/tile_set.png", sf::Vector2u(16, 16))) {
    std::cerr << "Error loading map graphics" << std::endl;
  }
  std::cout << "Map Initialised" << std::endl;
}

/* Get the variables and clauses from the SAT solver
------------------------------------------------------------------------------*/
void TileMap::SetSATParameters(ZChaffManager zchaff_manager) {
  num_clauses_     = zchaff_manager.GetNumClauses();
  num_variables_   = zchaff_manager.GetNumVariables();

  // each variable has two literals (e.g. x and ¬x)
  // therefore need two warp gadgets for each literal
  num_warp_gadgets = num_variables_ * 2;

  chunk_map_rows_    = SetChunkMapRows();
  chunk_map_columns_ = SetChunkMapColumns();

  CreateChunkMap(num_variables_, num_clauses_);
}

/* Establish the tilemap height and width from the chunk map
------------------------------------------------------------------------------*/
void TileMap::GetChunkMapParameters() {
  tilemap_height_ = 0;
  tilemap_width_  = 0;
  var_row_width_  = 0;
  unsigned int temp_width = 0;

  // Get total height of map
  for (int i = 0; i < chunk_map_.size(); ++i) {
    tilemap_height_ += chunk_map_[i][0].chunk_height_;
  }

  // Get variable map width
  for (int j = 0; j < chunk_map_[0].size(); ++j) {
    // std::cout << "chunk name: " << chunk_map_[0][j].name_ << std::endl;
    // std::cout << "chunk width: " << chunk_map_[0][j].chunk_width_ << std::endl;
    temp_width += chunk_map_[0][j].chunk_width_;
    // std::cout << "temp width: " << temp_width << std::endl;
    std::cout << std::endl;
  }
  var_row_width_ += temp_width;
  std::cout << "var_row_width_: " << var_row_width_ << std::endl;
  std::cout << std::endl;

  // Get clause width
  temp_width = 0;
  unsigned int clause_row = num_variables_;
  for (int j = 0; j < chunk_map_[clause_row].size(); ++j) {
    std::cout << "chunk name:  " << chunk_map_[clause_row][j].name_ << std::endl;
    std::cout << "chunk width: " << chunk_map_[clause_row][j].chunk_width_ << std::endl;
    temp_width += chunk_map_[clause_row][j].chunk_width_;
    std::cout << "temp width: " << temp_width << std::endl;
    std::cout << std::endl;
  }
  tilemap_width_ += temp_width;
  std::cout << "tilemap width (after checkout): " << tilemap_width_ << std::endl;
  std::cout << std::endl;


  std::cout << " Fucn Tile Map Height : " << tilemap_height_ << std::endl;
  std::cout << " Fucn Tile Map Width  : " << tilemap_width_  << std::endl;
}

void TileMap::CreateChunkMap(unsigned int var, unsigned int clause) {
  chunk_map_.clear();

  // The Start Gadget happens only once and is a special case of variable
  std::vector<MapChunk> chunk_start_row;
  chunk_start_row.push_back(map_chunk_manager_.start_gadget_);
  for (int i = 0; i < 2; ++i) {
    chunk_start_row.push_back(map_chunk_manager_.warp_start_);
  }
  chunk_start_row.push_back(map_chunk_manager_.warp_end_);

  // Set the tile_map up for the Start Gadget



  // The Start Gadget happens only once and is a special case of variable
  std::vector<MapChunk> innerstart;
  innerstart.push_back(map_chunk_manager_.start_gadget_);
  for (int i = 0; i < 2; ++i) {
    innerstart.push_back(map_chunk_manager_.warp_start_);
    for (int i = 0; i < clause; ++i) {
      innerstart.push_back(map_chunk_manager_.warp_pipe_);
    }
    innerstart.push_back(map_chunk_manager_.warp_end_);
  }

  std::vector<MapChunk> innervar;
  innervar.push_back(map_chunk_manager_.variable_gadget_);
  for (int i = 0; i < 2; ++i) {
    innervar.push_back(map_chunk_manager_.warp_start_);
    for (int i = 0; i < clause; ++i) {
      innervar.push_back(map_chunk_manager_.warp_pipe_);
    }
    innervar.push_back(map_chunk_manager_.warp_end_);
  }

  std::vector<MapChunk> innerend;
  innerend.push_back(map_chunk_manager_.check_in_);
  for (int m = 0; m < clause; ++m) {
    innerend.push_back(map_chunk_manager_.clause_);
  }
  innerend.push_back(map_chunk_manager_.finish_gadget_);

  // Add the variable gadget vector for remaining variables
  // var - 1 for Start Gadget
  // var - 1 for Variable Gadget
  chunk_map_.push_back(innerstart);
  for (int i = 0; i < var - 1; ++i) {
    chunk_map_.push_back(innervar);
  }
  chunk_map_.push_back(innerend);
  std::cout << "Chunk Map complete" << std::endl;
  PrintChunkMap();

  GetChunkMapParameters();

  // unsigned int padding = tilemap_width_ - innerstart.size();
  // std::cout << "innerstart size = " << innerstart.size() << std::endl;
  // std::cout << "Padding         = " << padding << std::endl;

  SetPadding(innerstart);

}

void TileMap::SetPadding(std::vector<MapChunk> var) {
  var_row_width_ = 0;

  for (int i = 0; i < var.size(); ++i) {
    var_row_width_ += var[i].chunk_width_;
  }
  std::cout << " Var Row : " << var_row_width_  << std::endl;

  unsigned int padding = tilemap_width_ - var_row_width_;
  std::cout << "Padding         = " << padding << std::endl;
}

unsigned int TileMap::SetChunkMapRows() {
  return num_variables_ + 2;
}

unsigned int TileMap::SetChunkMapColumns() {
  // The warp gadget has a start and beginning (+2 columns)
  // each variable has two literals (e.g. x and ¬x) so multiple * 2
  warp_columns_ = (num_clauses_ + 2) * 2;

  // The checkout gadget has a check in gadget (+1) and a finish gadget (+1)
  clause_checkout_columns_ = num_clauses_ + 2;

  //larger of the two
  return warp_columns_;
}

void TileMap::InitialiseTiles() {
  for (unsigned int i = 0; i < tilemap_height_; ++i) {
    std::vector<Tile> tmp_value;
    for (unsigned int j = 0; j < tilemap_width_; ++j) {
      tmp_value.push_back(Tile());
    }
    t_map_.push_back(tmp_value);
  }
  std::cout << "Chunk to Tile map complete" << std::endl;
}

void TileMap::ChunkToTileMap() {
  std::ifstream map_chunk_values;
  InitialiseTiles();
  for (unsigned int i = 0; i < chunk_map_.size(); ++i) {
    for (unsigned int j = 0; j < chunk_map_[i].size(); ++j) {
      map_chunk_values.open(chunk_map_[i][j].file_path_);
    }

  }
  // std::cout << "Chunk to Tile map complete" << std::endl;
}

void TileMap::AddStartGadget() {
  tilemap_height_ = map_chunk_manager_.start_gadget_.chunk_height_;
  tilemap_width_  = map_chunk_manager_.start_gadget_.chunk_width_;

  std::cout << "height = " << tilemap_height_ << std::endl;
  std::cout << "width = "  << tilemap_width_  << std::endl;

  ChunkReader(map_chunk_manager_.start_gadget_);
}

void TileMap::PrintChunkMap() {
  for (int i = 0; i < chunk_map_.size(); ++i) {
    for (int j = 0; j < chunk_map_[i].size(); ++j) {
      std::cout << chunk_map_[i][j].name_ << "       ";
    }
    std::cout << std::endl;
  }
}

void TileMap::ChunkReader(MapChunk chunk) {
  std::ifstream chunk_file(chunk.file_path_);
  // for (unsigned int i = 0; i < chunk.chunk_height_; ++i) {
  //   std::vector<Tile> tmp_value;
  //   for (unsigned int j = 0; j < chunk.chunk_width_; ++j) {
  //     tmp_value.push_back(Tile());
  //   }
  //   t_map_.push_back(tmp_value);
  // }
  // std::cout << "Added Tiles" << std::endl;
  int value;
  for (unsigned int i = 0; i < tilemap_height_; ++i) {
    for (unsigned int j = 0; j < tilemap_width_; ++j) {
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
  for (unsigned int i = 0; i < tilemap_height_; ++i) {
    std::vector<Tile> tmp_value;
    for (unsigned int j = 0; j < tilemap_width_; ++j) {
      tmp_value.push_back(Tile());
    }
    t_map_.push_back(tmp_value);
  }
}

void TileMap::SetParameters(std::string filepath) {
  std::ifstream mapfile(filepath);

  mapfile >> tilemap_width_ >> tilemap_height_;

  LoadTileObjects();

  int value;
  for (unsigned int i = 0; i < tilemap_height_; ++i) {
    for (unsigned int j = 0; j < tilemap_width_; ++j) {
      mapfile >> value;
      t_map_[i][j].SetTileValue(value);
    }
  }
  printf("Map values successfully inserted!\n");
  mapfile.close();
}
