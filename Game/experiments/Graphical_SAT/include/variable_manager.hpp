// Copyright 2015, Aaron Ceross

#ifndef VARIABLE_MANAGER_HPP
#define VARIABLE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "z_variable.hpp"
#include "y_variable.hpp"
#include "x_variable.hpp"
#include "var_object.hpp"
#include "../lib/zchaff/SAT.h"

class VariableManager {
 public:
  VariableManager();
  void LoadVariables(SAT_Manager SAT_manager);

  void GetNumVariables(int num_var);

  std::vector<VariableObject> variable_list_;
 private:
  int num_vars_;
};

#endif  // VARIABLE_MANAGER_HPP
