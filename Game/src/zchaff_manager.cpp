// Copyright 2015, Aaron Ceross

#include <set>
#include <functional>

#include "../include/zchaff_manager.hpp"

ZChaffManager::ZChaffManager() {
  SAT_manager_ = SAT_InitManager();
  std::cout << "ZChaffManager: SAT Manager Initialised." << std::endl;
}

void ZChaffManager::LoadInstance() {
  std::cout << "Loading SAT Instance" << std::endl;
  ReadSATFile();
  GetClauses();
  PrintSolution();
}

void ZChaffManager::ReadSATFile() {
  std::cout << std::endl;
  std::cout << "===== READING FILE ===== "<< std::endl;

  char line_buffer[MAX_LINE_LENGTH];
  char word_buffer[MAX_WORD_LENGTH];
  std::set <int> clause_vars;
  std::set <int> clause_lits;
  int line_num = 0;

  // File to be read
  std::string filename = "resources/SAT_instances/3SAT_Mario_Ben.cnf";

  std::ifstream inp(filename, std::ios::in);
  if (!inp) {
    std::cerr << "Can't open input file" << std::endl;
    exit(1);
  }
  while (inp.getline(line_buffer, MAX_LINE_LENGTH)) {
    ++line_num;
    if (line_buffer[0] == 'c') {
      continue;
    } else if (line_buffer[0] == 'p') {
        int var_num;
        int cl_num;

        int arg = sscanf(line_buffer, "p cnf %d %d", &var_num, &cl_num);
        if (arg < 2) {
          std::cerr << "Unable to read number of variables and clauses"
                    << "at line " << line_num << std::endl;
          exit(3);
        }
        SAT_SetNumVariables(SAT_manager_, var_num);
    // Clause definition or continuation
    } else {
        char *lp = line_buffer;
        do {
          char *wp = word_buffer;
          while (*lp && ((*lp == ' ') || (*lp == '\t'))) {
            lp++;
          }
          while (*lp && (*lp != ' ') && (*lp != '\t') && (*lp != '\n')) {
            *(wp++) = *(lp++);
          }
          *wp = '\0';  // terminate string

          if (strlen(word_buffer) != 0) {     // check if number is there
            int var_idx = atoi(word_buffer);
            int sign    = 0;

            if (var_idx != 0) {
              if (var_idx < 0) { var_idx = -var_idx; sign = 1; }
              clause_vars.insert(var_idx);
              clause_lits.insert((var_idx << 1) + sign);
            } else {
              // add this clause
              if (clause_vars.size() != 0 &&
                 (clause_vars.size() == clause_lits.size())) {
                std::vector <int> temp;
                for (std::set<int>::iterator itr = clause_lits.begin();
                     itr != clause_lits.end(); ++itr)
                  temp.push_back(*itr);
                SAT_AddClause(SAT_manager_, & temp.begin()[0], temp.size());
              // it contains var of both polarity
              // it therefore is automatically satisfied
              // just skip it
              } else {}
              clause_lits.clear();
              clause_vars.clear();
            }
          }
        }
        while (*lp);
    }
  }
  if (!inp.eof()) {
    std::cerr << "Input line " << line_num <<  " too long. Cannot continue..."
              << std::endl;
    exit(2);
  }
  // assert(clause_vars.size() == 0);
  // some benchmark has no 0 in the last clause
  if (clause_lits.size() && clause_vars.size() == clause_lits.size()) {
    std::vector<int> temp;
    for (std::set<int>::iterator itr = clause_lits.begin();
         itr != clause_lits.end(); ++itr)
      temp.push_back(*itr);
    SAT_AddClause(SAT_manager_, & temp.begin()[0], temp.size() );
  }
  clause_lits.clear();
  clause_vars.clear();
  std::cout << "...Successfully read CNF file..." << std::endl;

  // Assign values from zchaff to SAT manager instance
  num_variables_ = SAT_NumVariables(SAT_manager_);
  num_literals_  = SAT_NumLiterals(SAT_manager_);
  num_clauses_   = SAT_NumClauses(SAT_manager_);

  // Load the variables into variable manager
  var_manager_.LoadVariables(SAT_manager_);
}

void ZChaffManager::GetLiterals(int clause_index, int* literals) {
  int num_literals;
  num_literals = SAT_GetClauseNumLits(SAT_manager_, clause_index);

  for (unsigned int i = 0; i < num_literals; ++i) {
    literals[i] = var_manager_.clauses_[clause_index][i];
  }
}

void ZChaffManager::InitialiseClauseStructure() {
  for (unsigned int i = 0; i < num_clauses_; ++i) {
    std::vector<int> tmp_value;
    for (unsigned int j = 0; j < num_literals_; ++j) {
      tmp_value.push_back(j);
    }
    var_manager_.clauses_.push_back(tmp_value);
  }
}

void ZChaffManager::GetClauses() {
  InitialiseClauseStructure();
  // Only 3 literals in array as analysing 3SAT instances
  int clause_literals[3];
  int clause_index;
  int num_clause_literals;

  clause_index = SAT_GetFirstClause(SAT_manager_);

  for (int i = 0; i < num_clauses_; ++i) {
    std::cout << std::endl;
    std::cout << "Clause index: " << clause_index + 1 << std::endl;

    num_clause_literals = SAT_GetClauseNumLits(SAT_manager_, clause_index);
    std::cout << "Number of clause literals: " << num_clause_literals << std::endl;

    SAT_GetClauseLits(SAT_manager_, clause_index, clause_literals);

    for (int j = 0; j < num_clause_literals; ++j) {
      int true_literal = clause_literals[j];
      if (true_literal % 2) {
        true_literal = ((true_literal - 1) / 2) * -1;
      } else {
        true_literal = true_literal / 2;
      }
      std::cout << "True literal =  " << true_literal << std::endl;
      var_manager_.clauses_[i][j] = true_literal;
    }

    clause_index = SAT_GetNextClause(SAT_manager_, clause_index);
  }
  std::cout << std::endl;
}

void ZChaffManager::PrintSolution() {
  std::cout << std::endl;
  std::cout << "===== SOLUTION =====" << std::endl;

  if (satisfiability_result_ == UNSATISFIABLE) {
    std::cout << "No solution possible" << std::endl;
  } else {
    int s;

    for (int i = 0; i < num_variables_; ++i) {
      s = var_manager_.variable_list_[i].GetFinalValue();
      if (s < 0) {
        assignment_ = "FALSE";
      } else {
        assignment_ = "TRUE";
      }
      std::cout << "Variable " << i + 1 << ": " << assignment_ << std::endl;
    }
    std::cout << std::endl;
  }
}

ZChaffManager::~ZChaffManager() {}
