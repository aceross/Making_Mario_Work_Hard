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
#include "map_chunk_manager.hpp"
#include "zchaff_manager.hpp"

class TileMap : public sf::Sprite {
 public:
  using sf::Drawable::draw;
  TileMap();
  ~TileMap();
  bool LoadMap(const std::string& tileset, sf::Vector2u tileSize);
  void InitialiseMap(ZChaffManager zchaff_manager);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  //test function
  void CreateChunkMap(unsigned int var, unsigned int clause);
  std::vector< std::vector<std::string> > test_map_;

  sf::VertexArray vertices_;
  sf::Texture     tileset_;
  sf::Sprite      tiles_;
  std::vector<std::vector< Tile> > t_map_;

  MapChunkManager map_chunk_manager_;
  std::vector< std::vector<MapChunk> > chunk_map_;

  unsigned int tilemap_height_;
  unsigned int tilemap_width_;

  unsigned int row_count_;
  unsigned int column_count_;

  unsigned int num_clauses_;
  unsigned int num_variables_;
  unsigned int num_warp_gadgets;

 private:
  // Procedural content generation - Map Generation
  void SetSATParameters(ZChaffManager zchaff_manager);

  void ChunkReader(MapChunk chunk);

  void AddStartGadget();

  void AddWarpGadget();
  void AddWarpStart();
  void AddWarpPipe();
  void AddWarpExit();

  void AddVariableGadget();

  void AddCheckinGadget();
  void AddClauseGadget();
  void AddFinishGadget();

  void ChunkToTileMap();
  void InitialiseChunkMap();
  unsigned int SetChunkMapRows();
  unsigned int SetChunkMapColumns();

  void PrintChunkMap();

  unsigned int chunk_map_rows_;
  unsigned int chunk_map_columns_;
  unsigned int warp_columns_;
  unsigned int clause_checkout_columns_;
  unsigned int max_column_length_;

 private:
  // For collision
  sf::FloatRect GetLocalBounds() const;
  sf::FloatRect GetGlobalBounds() const;

  void LoadTileObjects();
  void SetParameters(std::string filepath);
  void ResizeMap(int width, int height);
  void PrintMap();
};

#endif  // TILE_MAP_HPP
