// Copyright 2015, Aaron Ceross

#ifndef STATIC_TILED_MAP_INCLUDED
#define STATIC_TILED_MAP_INCLUDED
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class TileLoader;   // forward declaration for pointer

class StaticTiledMap : public sf::Drawable {
 private:
  // change values of these to match your needs and improve performance
  enum { tilesize = 32, chunksize = 32 };
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::Texture m_texture;
  // map x and y - dimensions of map in tiles, chunks x and y - amount of chunks
  int map_x, map_y, chunks_x, chunks_y;
  std::vector<std::vector<sf::VertexArray> > m_chunks;
 public:
  StaticTiledMap(void);
  virtual ~StaticTiledMap(void) {}
  void LoadFrom(TileLoader* gloader);
};

#endif  // STATIC_TILED_MAP_INCLUDED
