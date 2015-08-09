
#include <SFML/Graphics/RenderTarget.hpp>
#include "../include/map_node.hpp"

MapNode::MapNode()
: ml_("resources/maps/")
{}

void MapNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(ml_);
}
