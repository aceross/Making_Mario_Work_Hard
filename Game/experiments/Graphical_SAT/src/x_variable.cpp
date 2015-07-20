// Copyright 2015, Aaron Ceross

#include "../include/x_variable.hpp"

X_Variable::X_Variable() {}

void X_Variable::SetID(int id) {
  this->id_ = id;
}

int X_Variable::GetID() {
  return id_;
}

void X_Variable::SetInitialValue(int initial_value) {
  this->initial_value_ = initial_value;
}

int X_Variable::GetInitialValue() {
  return initial_value_;
}

void X_Variable::SetDecisionValue(int decision_value) {
  this->decision_value_ = decision_value;
}

int X_Variable::GetDecisionValue() {
  return decision_value_;
}

void X_Variable::SetFinalValue(int final_value) {
  this->final_value_ = final_value;
}

int X_Variable::GetFinalValue() {
  return final_value_;
}
