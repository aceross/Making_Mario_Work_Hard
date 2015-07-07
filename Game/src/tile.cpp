// Copyright 2015, Aaron Ceross

#include "../include/tile.hpp"

Tile::Tile() {}
Tile::~Tile() {}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {}

/* Tile ID
------------------------------------------------------------------------------*/
int Tile::GetTileID() {
  return id_;
}

void Tile::SetTileID(int id) {
  id_ = id;
}

/* Tile Value
------------------------------------------------------------------------------*/
int Tile::GetTileValue() {
  return tile_value_;
}

void Tile::SetTileValue(int value) {
  tile_value_ = value;
}

/* Tile Position
------------------------------------------------------------------------------*/
sf::Vector2f Tile::GetTilePosition() {
  return tile_position_;
}

void Tile::SetTilePosition(sf::Vector2f position) {
  tile_position_ = position;
}
