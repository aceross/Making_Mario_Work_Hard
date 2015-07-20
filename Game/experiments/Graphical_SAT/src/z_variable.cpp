// Copyright 2015, Aaron Ceross

#include "../include/z_variable.hpp"

Z_Variable::Z_Variable() {}

void Z_Variable::SetID(int id) {
  this->id_ = id;
}

int Z_Variable::GetID() {
  return id_;
}

void Z_Variable::SetInitialValue(int initial_value) {
  this->initial_value_ = initial_value;
}

int Z_Variable::GetInitialValue() {
  return initial_value_;
}

void Z_Variable::SetDecisionValue(int decision_value) {
  this->decision_value_ = decision_value;
}

int Z_Variable::GetDecisionValue() {
  return decision_value_;
}

void Z_Variable::SetFinalValue(int final_value) {
  this->final_value_ = final_value;
}

int Z_Variable::GetFinalValue() {
  return final_value_;
}
