
#include <SFML/Graphics/RenderTarget.hpp>
#include "../include/map_node.hpp"

MapNode::MapNode()
: tile_map_()
{

}

void MapNode::GenerateMap() {
  unsigned int height = tile_map_.GetTileMapHeight();
  unsigned int width  = tile_map_.GetTileMapHeight();

  for (int i = 0; i < height; ++i) {
    for (int j = 0; i < width; ++j) {

    }

  }
}

void MapNode::DrawCurrent(sf::RenderTarget& target,
                          sf::RenderStates states) const {
  target.draw(tile_map_);
}
