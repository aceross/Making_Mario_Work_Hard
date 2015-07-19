// Copyright 2015, Aaron Ceross

#ifndef Y_VARIABLE_HPP
#define Y_VARIABLE_HPP

#include <SFML/Graphics.hpp>

class Y_Variable : public sf::RectangleShape {
 public:
  Y_Variable();
 private:
  int value_;
 public:
  void SetValue(int value);
  int  GetValue();
};

#endif  // Y_VARIABLE_HPP
