// Copyright 2015, Aaron Ceross
#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable, public sf::Transformable, public sf::Sprite {
 public:
  Tile();
  ~Tile();

  int GetTileID();
  void SetTileID(int id);

  int GetTileValue();
  void SetTileValue(int value);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  int id_;
  int tile_value_;
};

#endif  // TILE_HPP
