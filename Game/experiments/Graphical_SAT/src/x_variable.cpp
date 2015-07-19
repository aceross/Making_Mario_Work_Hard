// Copyright 2015, Aaron Ceross

#include "../include/x_variable.hpp"

X_Variable::X_Variable() {}

void X_Variable::SetValue(int value) {
  value_ = value;
}

int X_Variable::GetValue() {
  return value_;
}
