// Copyright 2015, Aaron Ceross

#ifndef VARIABLE_OBJECT_HPP
#define VARIABLE_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class VariableObject {
 public:
  VariableObject();
  void SetID(int id);
  int  GetID();

  void SetInitialValue(int initial_value);
  int  GetInitialValue();

  void SetDecisionValue(int decision_value);
  int  GetDecisionValue();

  void SetFinalValue(int final_value);
  int  GetFinalValue();

  void SetClauseLocation(int clause_number);
  int  GetClauseLocations();

 public:
  sf::CircleShape circle_;
  std::vector<int> clause_location_;
 private:
  int id_;
  int initial_value_;
  int decision_value_;
  int final_value_;

  std::vector<int> clause_locations_;
};

#endif  // VARIABLE_OBJECT_HPP
