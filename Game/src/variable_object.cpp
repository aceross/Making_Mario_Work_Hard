// Copyright 2015, Aaron Ceross

#include "../include/variable_object.hpp"

VariableObject::VariableObject() {}

void VariableObject::SetID(int id) {
  id_ = id;
}

int VariableObject::GetID() {
  return id_;
}

void VariableObject::SetInitialValue(int initial_value) {
  initial_value_ = initial_value;
}

int VariableObject::GetInitialValue() {
  return initial_value_;
}

void VariableObject::SetDecisionValue(int decision_value) {
  decision_value_ = decision_value;
}

int VariableObject::GetDecisionValue() {
  return decision_value_;
}

void VariableObject::SetFinalValue(int final_value) {
  final_value_ = final_value;
}

int VariableObject::GetFinalValue() {
  return final_value_;
}
