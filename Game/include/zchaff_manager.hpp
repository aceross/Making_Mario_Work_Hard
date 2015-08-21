// Copyright 2015, Aaron Ceross

#ifndef ZCHAFF_MANAGER_HPP
#define ZCHAFF_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include "../lib/zchaff/SAT.h"
#include "variable_manager.hpp"

// Values for parsing file
#define MAX_LINE_LENGTH 65536
#define MAX_WORD_LENGTH 64

class ZChaffManager {
 private:
  SAT_Manager     SAT_manager_;
  VariableManager var_manager_;

  unsigned int num_variables_;
  unsigned int num_literals_;
  unsigned int num_clauses_;

  int satisfiability_result_;
  std::string assignment_;
 public:
  ZChaffManager();
  void LoadInstance();
  void GetLiterals(int clause_index, int* literals);
  ~ZChaffManager();
private:
  void ReadSATFile();
  void InitialiseClauseStructure();
  void GetClauses();
  void Solve();
  void PrintSolution();
};

#endif  // ZCHAFF_MANAGER_HPP
