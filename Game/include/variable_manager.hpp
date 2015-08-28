// Copyright 2015, Aaron Ceross

#ifndef VARIABLE_MANAGER_HPP
#define VARIABLE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "variable_object.hpp"
#include "../lib/zchaff/SAT.h"

class VariableManager {
 public:
  VariableManager();
  void LoadVariables(SAT_Manager SAT_manager);
  void SetNumVariables(int num_var);
  void SetFinalVarValues(int final_value);

  unsigned int GetNumVariables();
  unsigned int GetNumClauses();

  void LoadNumClauses(SAT_Manager SAT_manager);
  void AssignLiterals(SAT_Manager SAT_manager);

  std::vector<VariableObject> variable_list_;
  std::vector<std::vector< int > > clauses_;

 private:
  unsigned int num_vars_;
  unsigned int num_clauses_;
};

#endif  // VARIABLE_MANAGER_HPP
