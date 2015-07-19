// Copyright 2015, Aaron Ceross

#ifndef Z_VARIABLE_HPP
#define Z_VARIABLE_HPP

#include <SFML/Graphics.hpp>

class Z_Variable : public sf::CircleShape {
 public:
  Z_Variable();
 private:
  int value_;
 public:
  void SetValue(int value);
  int  GetValue();
};

#endif  //  Z_VARIABLE_HPP
