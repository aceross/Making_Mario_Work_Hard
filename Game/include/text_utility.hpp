// Copyright 2015, Aaron Ceross

#ifndef TEXT_UTILITY_HPP
#define TEXT_UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>
#include <string>

namespace sf {
class Sprite;
class Text;
}

class Animation;

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
void CentreOrigin(sf::Sprite& sprite);
void CentreOrigin(sf::Text& text);
void CentreOrigin(Animation& animation);

// Degree/radian conversion
float  toDegree(float radian);
float  toRadian(float degree);

// Random number generation
int    randomInt(int exclusiveMax);

// Vector operations
float         length(sf::Vector2f vector);
sf::Vector2f  unitVector(sf::Vector2f vector);

#endif  // TEXT_CENTERING_UTILITY_HPP
