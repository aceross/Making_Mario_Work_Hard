// Copyright 2015, Aaron Ceross

#include "../include/z_variable.hpp"

Z_Variable::Z_Variable() {}

void Z_Variable::SetValue(int value) {
  value_ = value;
}

int Z_Variable::GetValue() {
  return value_;
}
