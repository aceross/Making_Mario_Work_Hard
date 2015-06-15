// Copyright 2015, Aaron Ceross

#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>

class InputManager {
 public:
  static sf::Event event;
  static bool IsKeyPressed(const sf::Keyboard::Key key);
};

#endif  // INPUT_MANAGER_HPP
