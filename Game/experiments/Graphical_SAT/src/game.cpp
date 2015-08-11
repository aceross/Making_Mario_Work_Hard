// Copyright 2015, Aaron Ceross

#include <string>
#include <set>
#include <vector>
#include <functional>

#include "../include/game.hpp"

Game::Game() {
  // InitialiseWindow();
  LoadAssets();
  SAT_manager_ = SAT_InitManager();
}

void Game::InitialiseWindow() {
  settings_.antialiasingLevel = 8;
  window_.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                               "Graphical SAT Solver",
                                sf::Style::Default, settings_);
  window_.setFramerateLimit(60);
}

void Game::LoadAssets() {
  if (!font_.loadFromFile("font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }

  InitialiseTexts();
}

void Game::InitialiseTexts() {
  // Load the title text
  title_text_.setFont(font_);
  title_text_.setColor(sf::Color::Black);
  title_text_.setString("Graphical SAT Solver");
  title_text_.setPosition(275, 0);

  // Load the instance text
  instance_text_.setFont(font_);
  instance_text_.setColor(sf::Color::Black);
  instance_text_.setCharacterSize(17);
  // instance_text_.setString(170);
  instance_text_.setPosition(300, 300);

  // Load initial problem text
}

// Adapted from the zchaff library
void Game::ReadFile() {
  std::cout << std::endl;
  std::cout << "===== READING FILE ===== "<< std::endl;

  char line_buffer[MAX_LINE_LENGTH];
  char word_buffer[MAX_WORD_LENGTH];
  std::set <int> clause_vars;
  std::set <int> clause_lits;
  int line_num = 0;

  std::string filename = "lib/zchaff/problems/unsolved.cnf";

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
    std::cerr << "Input line " << line_num <<  " too long. Can't continue..."
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
  // std::cout << "\tSuccessfully read CNF file..." << std::endl;

  // Assign values from SAT manager to Game class instance
  num_variables_ = SAT_NumVariables(SAT_manager_);
  num_literals_  = SAT_NumLiterals(SAT_manager_);
  num_clauses_   = SAT_NumClauses(SAT_manager_);

  // Load the variables into variable manager
  var_mngr.LoadVariables(SAT_manager_);
}

void Game::InitialiseCircles() {
  for (int i = 0; i < num_variables_; ++i) {
    if (i == 0) {
      objects_.push_back(sf::CircleShape(15));
      // std::cout << "Variable 1 added" << std::endl;
      objects_[i].setFillColor(sf::Color(172, 30, 30));  // red
      objects_[i].setPosition(250, 250);
    }
    if (i == 1) {
      objects_.push_back(sf::CircleShape(18, 3));
      // std::cout << "Variable 2 added" << std::endl;
      objects_[i].setFillColor(sf::Color(172, 30, 30));  // red
      objects_[i].setPosition(300, 250);
    }
    if (i == 2) {
      objects_.push_back(sf::CircleShape(15, 4));
      // std::cout << "Variable 3 added" << std::endl;
      objects_[i].setFillColor(sf::Color(172, 30, 30));  // red
      objects_[i].setPosition(350, 250);
    }
  }
}

void Game::Solve() {
  std::cout << "Number of variables:  " << num_variables_ << std::endl;
  std::cout << "Number of literals:   " << num_literals_  << std::endl;
  std::cout << "Number of clauses:    " << num_clauses_   << std::endl;

  satisfiability_result_ = SAT_Solve(SAT_manager_);

  for (int i = 1, sz = SAT_NumVariables(SAT_manager_); i <= sz; ++i) {
    if (SAT_GetVarAsgnment(SAT_manager_, i) == 1) {
      var_mngr.variable_list_[i-1].SetFinalValue(i);
      // std::cout << "Value Inserted" << std::endl;
    }
    if (SAT_GetVarAsgnment(SAT_manager_, i) == 0) {
      var_mngr.variable_list_[i-1].SetFinalValue(i * (-1));
      // std::cout << "Value Inserted" << std::endl;
    }
  }
  DisplayResults(SAT_manager_, satisfiability_result_);
  PrintSolution();
  InitialiseCircles();
}

void Game::DisplayResults(SAT_Manager SAT_manager_, int outcome) {
  std::cout << std::endl;
  std::cout << "===== SATISFIABILITY =====" << std::endl;
  std::string result = "UNKNOWN";

  switch (outcome) {
    case SATISFIABLE:
      std::cout << "Instance SATISFIABLE" << std::endl;

      // following lines will print out a solution if a solution exist
      for (int i = 1, sz = SAT_NumVariables(SAT_manager_); i <= sz; ++i) {
        switch (SAT_GetVarAsgnment(SAT_manager_, i)) {
          case -1:
            std::cout << "(" << i << ")";
            break;
          case 0:
            std::cout << "-" << i;
            // var_mngr.variable_list_[i].SetFinalValue(i * -1);
            // printf("Negative Value inserted\n");
            break;
          case 1:
            std::cout << i;
            // var_mngr.variable_list_[i].SetFinalValue(i);
            // printf("Positive Value inserted\n");
            break;
          default:
            std::cerr << "Unknown variable value state" << std::endl;
            exit(4);
        }
        std::cout << " ";
      }
      result  = "SAT";
      break;
  case UNSATISFIABLE:
    result  = "UNSAT";
    std::cout << "Instance UNSATISFIABLE" << std::endl;
    break;
  case TIME_OUT:
    result  = "ABORT : TIME OUT";
    std::cout << "Time out, unable to determine satisfiability" << std::endl;
    break;
  case MEM_OUT:
    result  = "ABORT : MEM OUT";
    std::cout << "Memory out, unable to determine satisfiability" << std::endl;
    break;
  default:
    std::cerr << "Unknown outcome" << std::endl;
  }
  printf("\n");
}

void Game::Run() {
  ReadFile();
  Solve();

  while (window_.isOpen()) {
    HandleEvents();
    Draw();
  }
}

// Give the variables a decision
void Game::Decision(SAT_Manager SAT_manager_) {
  num_variables_ = SAT_NumVariables(SAT_manager_);
  num_literals_  = SAT_NumLiterals(SAT_manager_);

  int i;
  std::cout << "SAT Number of Variables =  " << num_variables_ << std::endl;
  std::cout << "SAT Number of Literals  =  " << num_literals_  << std::endl;
  // int result;
  int check;

  for (i = 1; i < num_variables_; ++i) {
    check = SAT_GetVarAsgnment(SAT_manager_, i);
    printf("Variable %d value = %d\n", i, check);
    printf("\n");
    if (SAT_GetVarAsgnment(SAT_manager_, i) == UNKNOWN) {
      check = SAT_GetVarAsgnment(SAT_manager_, i);
      printf("VAR is UNKNOWN\n");
      printf("Variable %d value = %d\n", i, check);
      SAT_MakeDecision(SAT_manager_, i, 1);  // make decision with value 0;
      break;
    }
  }
  // every var got an assignment, no free var left
  if (i >= num_variables_) {
    check = SAT_GetVarAsgnment(SAT_manager_, i);
    printf("Variable %d value = %d\n", i, check);
    SAT_MakeDecision(SAT_manager_, 0, 0);
    check = SAT_GetVarAsgnment(SAT_manager_, i);
  }
}

void Game::HandleEvents() {
  while (window_.pollEvent(event_)) {
    switch (event_.type) {
      // Close window
      case sf::Event::Closed:
        window_.close();
        break;
      default: break;
    }
  }
}

void Game::Draw() {
  window_.clear(sf::Color(227, 227, 227));  // off-white

  // Decision();

  window_.draw(title_text_);
  window_.draw(instance_text_);
  // window_.draw(circle_);

  for (int i = 0; i < num_variables_; ++i) {
    window_.draw(objects_[i]);
  }

  window_.display();
}

void Game::PrintSolution() {
  if (satisfiability_result_ == UNSATISFIABLE) {
    std::cout << "No solution possible" << std::endl;
  } else {
    int s;
    // std::cout << "\tPrinting solution..." << std::endl;
    std::cout << std::endl;
    std::cout << "===== SOLUTION =====" << std::endl;
    for (int i = 0; i < num_variables_; ++i) {
      s = var_mngr.variable_list_[i].GetFinalValue();
      if (s < 0) {
        assignment_ = "FALSE";
      } else {
        assignment_ = "TRUE";
      }
      std::cout << "Variable " << i + 1 << ": " << assignment_ << std::endl;
    }
    printf("\n");
  }
}

Game::~Game() {}
