// Copyright 2015, Aaron Ceross
#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile : public sf::Sprite {
 public:
  Tile();
  ~Tile();

  int GetTileID();
  void SetTileID(int id);

  int GetTileValue();
  void SetTileValue(int value);

  sf::Vector2f GetTilePosition();
  void SetTilePosition(sf::Vector2f position);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  int id_;
  int tile_value_;
  sf::Vector2f tile_position_;
};

#endif  // TILE_HPP
