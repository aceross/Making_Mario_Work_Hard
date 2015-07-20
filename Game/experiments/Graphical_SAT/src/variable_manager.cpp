// Copyright 2015, Aaron Ceross
#include <vector>
#include "../include/variable_manager.hpp"

VariableManager::VariableManager() {}

void VariableManager::LoadVariables(SAT_Manager SAT_manager) {
  num_vars_ = SAT_NumVariables(SAT_manager);
  for (int i = 0; i < num_vars_; ++i) {
    variable_list_.push_back(VariableObject());
    variable_list_[i].SetID(i);
  }
}

void VariableManager::SetNumVariables(int num_var) {
  num_vars_ = num_var;
}

void VariableManager::SetFinalVarValues(int final_value) {}
