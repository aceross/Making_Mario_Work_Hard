// Copyright 2015, Aaron Ceross

#include "../include/y_variable.hpp"

Y_Variable::Y_Variable() {}

void Y_Variable::SetID(int id) {
  this->id_ = id;
}

int Y_Variable::GetID() {
  return id_;
}

void Y_Variable::SetInitialValue(int initial_value) {
  this->initial_value_ = initial_value;
}

int Y_Variable::GetInitialValue() {
  return initial_value_;
}

void Y_Variable::SetDecisionValue(int decision_value) {
  this->decision_value_ = decision_value;
}

int Y_Variable::GetDecisionValue() {
  return decision_value_;
}

void Y_Variable::SetFinalValue(int final_value) {
  this->final_value_ = final_value;
}

int Y_Variable::GetFinalValue() {
  return final_value_;
}
