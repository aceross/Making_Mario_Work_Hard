// Copyright 2015, Aaron Ceross

#include "../include/y_variable.hpp"

Y_Variable::Y_Variable() {}

void Y_Variable::SetValue(int value) {
  value_ = value;
}

int Y_Variable::GetValue() {
  return value_;
}
