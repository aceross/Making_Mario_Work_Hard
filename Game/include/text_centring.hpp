// Copyright 2015, Aaron Ceross

#ifndef TEXT_UTILITY_HPP
#define TEXT_UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <sstream>
#include <string>

namespace sf {
class Sprite;
class Text;
}

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
void CentreOrigin(sf::Sprite& sprite);
void CentreOrigin(sf::Text& text);

#endif  // TEXT_CENTERING_UTILITY_HPP
