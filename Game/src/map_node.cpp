
#include <SFML/Graphics/RenderTarget.hpp>
#include "../include/map_node.hpp"

MapNode::MapNode()
: tile_map_()
{}

void MapNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(tile_map_);
}
