// Copyright 2015, Aaron Ceross

#ifndef TILE_LOADER_INCLUDED
#define TILE_LOADER_INCLUDED

#include <SFML/Graphics/VertexArray.hpp>
#include <string>

struct MapData {
  std::string TextureName;
  int MapX, MapY;
  MapData(void):MapX(0), MapY(0) {}
};

// this is the class you must derieve from and complete following 2 tasks :
class TileLoader {
 protected:
  // 1. fill this struct with name of texture and map dimensions(in tiles)
  MapData m_mapdata;
 public:
  virtual ~TileLoader(void) {}
  virtual void AppendTile(int gx, int gy, sf::VertexArray& garr) = 0;

 /*
 2. implement this method to append(or skip appending) tiles(4 vertices) to
    given vertex array,

    you may assume tiles will be requested in row major order:((0,0),(1,0),..,
    (map_x-1,0),(0,1),..,(map_x-1,map_y-1)),

    this method will be called exactly MapX*MapY times,

    for correct displaying and culling it's assumed your appended tile will be
    square with side equal to tilesize and have it's top left point at
    (tilesize * gx,tilesize * gy)
 */

  const MapData& GetData(void) const { return m_mapdata; }
};

#endif  // TILE_LOADER_INCLUDED
