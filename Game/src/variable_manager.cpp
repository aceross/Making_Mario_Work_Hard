// Copyright 2015, Aaron Ceross
#include <vector>
#include <iostream>
#include "../include/variable_manager.hpp"

VariableManager::VariableManager() {}

void VariableManager::LoadVariables(SAT_Manager SAT_manager) {
  num_vars_ = SAT_NumVariables(SAT_manager);
  num_clauses_ = SAT_NumClauses(SAT_manager);

  for (int i = 0; i < num_vars_; ++i) {
    variable_list_.push_back(VariableObject());
    variable_list_[i].SetInitialValue(i);
  }
}

void VariableManager::SetLiteralLocations(int true_literal) {
  // for (int i = 0; i < num_vars_; ++i) {
  //   std::vector<int> lit;
  //   for (int j = 0; j < num_clauses_; ++j) {
  //     int l = clauses_[i][j];
  //     std::cout << "Lit: " << l << std::endl;
  //     if (IsUniqueLit(true_literal)) {
  //       lit.push_back(l);
  //     }
  //   }
  // }
}

bool VariableManager::IsUniqueLit(int true_literal) {
  for (int i = 0; i < clauses_.size(); ++i) {
    for (int j = 0; j < clauses_[i].size(); ++j) {
      if (true_literal == clauses_[i][j]) {
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

void VariableManager::SetNumVariables(int num_var) {
  num_vars_ = num_var;
}

void VariableManager::SetFinalVarValues(int final_value) {
  // Get SAT_manager and then push iterate and push to
}

void VariableManager::LoadNumClauses(SAT_Manager SAT_manager) {

}

void VariableManager::AssignLiterals(SAT_Manager SAT_manager) {

}

unsigned int VariableManager::GetNumClauses() {
  return num_clauses_;
}

unsigned int VariableManager::GetNumVariables() {
  return num_vars_;
}
