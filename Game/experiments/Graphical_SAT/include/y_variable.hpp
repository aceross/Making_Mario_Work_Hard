// Copyright 2015, Aaron Ceross

#ifndef Y_VARIABLE_HPP
#define Y_VARIABLE_HPP

#include <SFML/Graphics.hpp>
#include "var_object.hpp"

class Y_Variable : public VariableObject, public sf::RectangleShape {
 public:
  Y_Variable();

 private:
  int id_;
  int initial_value_;
  int decision_value_;
  int final_value_;

 public:
  void SetID(int id);
  int  GetID();

  void SetInitialValue(int initial_value);
  int  GetInitialValue();

  void SetDecisionValue(int decision_value);
  int  GetDecisionValue();

  void SetFinalValue(int final_value);
  int  GetFinalValue();
};

#endif  // Y_VARIABLE_HPP
