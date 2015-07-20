// Copyright 2015, Aaron Ceross

#ifndef VARIABLE_OBJECT_HPP
#define VARIABLE_OBJECT_HPP

#include <SFML/Graphics/Sprite.hpp>

class VariableObject {
 public:
  VariableObject();
  virtual void SetID(int id);
  virtual int GetID();

  virtual void SetInitialValue(int initial_value);
  virtual int GetInitialValue();

  virtual void SetDecisionValue(int decision_value);
  virtual int GetDecisionValue();

  virtual void SetFinalValue(int final_value);
  virtual int GetFinalValue();

 private:
  int id_;
  int initial_value_;
  int decision_value_;
  int final_value_;
};

#endif  // VARIABLE_OBJECT_HPP
