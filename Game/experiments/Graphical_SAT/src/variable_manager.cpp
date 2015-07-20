// Copyright 2015, Aaron Ceross
#include <vector>
#include "../include/variable_manager.hpp"

VariableManager::VariableManager() {}

void VariableManager::LoadVariables(SAT_Manager SAT_manager) {
  num_vars_ = SAT_NumVariables(SAT_manager);
  for (int i = 0; i < num_vars_; ++i) {
    std::vector<int> temp;
    if (i == 0) {
      // create X Variable
      // Assign initial values (id, init value)
    }
    if (i == 1) {
      // create Y Variable
      // Assign initial values (id, init value)
    }
    if (i == 2) {
      // create Z Variable
      // Assign initial values (id, init value)
    }
  }
}
void VariableManager::GetNumVariables(int num_var) {
  num_vars_ = num_var;
}
