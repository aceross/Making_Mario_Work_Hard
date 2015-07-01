// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <vector>
#include "../include/static_tiled_map.hpp"
#include "../include/tile_loader.hpp"


void StaticTiledMap::draw(sf::RenderTarget& target,
                          sf::RenderStates states) const {
  int left = 0, right = 0, top = 0, bottom = 0;

// get chunk indices into which top left and bottom right points of view fall:

  // get top left point of view
  sf::Vector2f temp = target.getView().getCenter() -
                     (target.getView().getSize()/2.f);

  left   = static_cast<int>(temp.x / (chunksize * tilesize));
  top    = static_cast<int>(temp.y/(chunksize*tilesize));

  // get bottom right point of view
  temp  += target.getView().getSize();

  right  = 1 + static_cast<int>(temp.x / (chunksize * tilesize));
  bottom = 1 + static_cast<int>(temp.y / (chunksize * tilesize));

  // clamp these to fit into array bounds:
  left   = std::max(0, std::min(left, chunks_x));
  top    = std::max(0, std::min(top, chunks_y));
  right  = std::max(0, std::min(right, chunks_x));
  bottom = std::max(0, std::min(bottom, chunks_y));

  // set texture and draw visible chunks:
  states.texture = &m_texture;
  for (int ix = left; ix < right; ++ix) {
    for (int iy = top; iy < bottom; ++iy) {
      target.draw(m_chunks[ix][iy], states);
    }
  }
}

StaticTiledMap::StaticTiledMap(void):
map_x(0), map_y(0), chunks_x(0), chunks_y(0)
{}

void StaticTiledMap::LoadFrom(TileLoader* gloader) {
  m_texture.loadFromFile(gloader->GetData().TextureName);
  map_x = gloader->GetData().MapX;
  map_y = gloader->GetData().MapY;

  // empty map - possibly forgotten to fill data struct
  if ((map_x * map_y) == 0) {
    // to stop displaying at all after failed loading:
    chunks_x = 0;
    chunks_y = 0;
    m_chunks.clear();
    return;
  }

  chunks_x = (map_x/chunksize) + 1;
  chunks_y = (map_y/chunksize) + 1;

  // ready up empty 2d arrays
  m_chunks.assign(chunks_x, std::vector<sf::VertexArray>(chunks_y,
                                                   sf::VertexArray(sf::Quads)));
  for (int iy = 0; iy < map_y; ++iy) {
    for (int ix = 0; ix < map_x; ++ix) {
      gloader->AppendTile(ix, iy, m_chunks[ix/chunksize][iy/chunksize]);
    }
  }
}
