// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/state_manager.hpp"

state_manager &state_manager::get_instance() {
  static state_manager instance;
  return instance;
}

state_manager::state_manager() {}
state_manager::~state_manager() {}

void state_manager::set_text(std::string text) {
  this->text = text;
}

void state_manager::draw_text() {
  std::cout << text << std::endl;
}
