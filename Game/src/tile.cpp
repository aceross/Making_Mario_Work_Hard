// Copyright 2015, Aaron Ceross

#include "../include/tile.hpp"

Tile::Tile() {}

Tile::~Tile() {}

int Tile::GetTileID() {
  return id_;
}

int Tile::GetTileValue() {
  return tile_value_;
}

void Tile::SetTileID(int id) {
  this->id_ = id;
}

void Tile::SetTileValue(int value) {
  this->tile_value_ = value;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {}
