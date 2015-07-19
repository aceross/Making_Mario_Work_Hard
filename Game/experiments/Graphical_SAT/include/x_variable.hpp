// Copyright 2015, Aaron Ceross

#ifndef X_VARIABLE_HPP
#define X_VARIABLE_HPP

#include <SFML/Graphics.hpp>

class X_Variable : public sf::CircleShape {
 public:
  X_Variable();
 private:
  int value_;
 public:
  void SetValue(int value);
  int  GetValue();
};

#endif  //  X_VARIABLE_HPP
