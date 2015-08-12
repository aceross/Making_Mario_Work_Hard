// Copyright 2015, Aaron Ceross

#include <string>
#include <set>
#include <vector>
#include <functional>

#include "../include/game.hpp"

Game::Game() {
  InitialiseWindow();
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
    std::cerr << "Could not find the requested font." << std::endl;
  }

  InitialiseTexts();
}

void Game::InitialiseTexts() {
  // Load the title text
  title_text_.setFont(font_);
  title_text_.setColor(sf::Color::Black);
  title_text_.setString("Graphical SAT Solver");
  title_text_.setPosition(275, 0);

  // Load the variable text
  variable_text_.setFont(font_);
  variable_text_.setColor(sf::Color::Black);
  variable_text_.setCharacterSize(25);
  variable_text_.setString("Variables:");
  variable_text_.setPosition(35, 80);

  // Load instance text
  instance_text_.setFont(font_);
  instance_text_.setColor(sf::Color::Black);
  instance_text_.setCharacterSize(25);
  instance_text_.setString("Clauses:");
  instance_text_.setPosition(35, 320);
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

  std::string filename = "lib/zchaff/problems/3SAT_Mario_Ben.cnf";

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

// red 172, 30, 30
// green 0, 138, 46
// grey 47, 50, 50
void Game::InitialiseVariableShapes() {
  sf::Vector2f position(150, 150);
  sf::Vector2f label_position(150, 110);

  char variable_name = 'A';

  for (int i = 0; i < num_variables_; ++i) {
    // Create variable label and circle object
    var_mngr.variable_list_[i].circle_ = sf::CircleShape(8);
    variable_label_.push_back(sf::Text());
    std::cout << "Variable" << i + 1 << "added" << std::endl;

    // Fill the colour
    var_mngr.variable_list_[i].circle_.setFillColor(sf::Color(47, 50, 50));
    // objects_[i].setFillColor(sf::Color(47, 50, 50));  // green
    variable_label_[i].setString(variable_name);
    variable_name++;

    // Add the positions
    variable_label_[i].setFont(font_);
    variable_label_[i].setColor(sf::Color::Black);
    variable_label_[i].setCharacterSize(25);
    variable_label_[i].setPosition(label_position);
    var_mngr.variable_list_[i].circle_.setPosition(position);
    // objects_[i].setPosition(position);

    // Increment the position for the next variable
    position.x += 40;
    label_position.x += 40;
  }
}

void Game::GetLiterals(int clause_index, int* literals) {
  int num_literals;
  num_literals = SAT_GetClauseNumLits(SAT_manager_, clause_index);

  for (int i = 0; i < num_literals; ++i) {
    literals[i] = var_mngr.clauses_[clause_index][i];
    std::cout << literals[i] << std::endl;
  }
}

void Game::InitialiseClauseShapes() {
  sf::Vector2f position(150, 150);
  sf::Vector2f label_position(75, 370);
  // sf::Vector2f
  int literals[20];

  for (int i = 0; i < num_clauses_; ++i) {
    clause_string_.push_back(sf::Text());
    clause_string_[i].setFont(font_);
    clause_string_[i].setColor(sf::Color::Black);
    clause_string_[i].setCharacterSize(18);

    // Get the literals
    GetLiterals(i, literals);

    clause_string_[i].setString("(  " + std::to_string(literals[0]) + "  v  " +
                               std::to_string(literals[1]) + "  v  " +
                               std::to_string(literals[2]) + "   )");
    clause_string_[i].setPosition(label_position);
    label_position.y += 40;
  }
}

void Game::InitialiseClauses(){
  for (unsigned int i = 0; i < num_clauses_; ++i) {
    std::vector<int> tmp_value;
    for (unsigned int j = 0; j < num_literals_; ++j) {
      tmp_value.push_back(j);
    }
    var_mngr.clauses_.push_back(tmp_value);
  }
}

void Game::GetClauses() {
  InitialiseClauses();
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
      var_mngr.clauses_[i][j] = true_literal;

      // Check that the variable is within this clause
      for (int k = 0; k < num_variables_; ++k) {
        int temp = var_mngr.variable_list_[k].GetInitialValue();
        if (true_literal == temp || true_literal == temp * -1) {
          // std::cout << "Do something" << std::endl;
        }
      }
    }

    clause_index = SAT_GetNextClause(SAT_manager_, clause_index);
  }
  std::cout << std::endl;
}

void Game::DisplayClauses() {
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

    // zchaff returns literals as even if positive or odd if negative
    // check to see if these is a modulous, then it's odd
    // subtract 1, divide by 2 (to get the original value), and make negative
    // otherwise simply divide by two
    for (int j = 0; j < num_clause_literals; ++j) {
      int true_literal = clause_literals[j];
      if (true_literal % 2) {
        true_literal = ((true_literal - 1) / 2) * -1;
      } else {
        true_literal = true_literal / 2;
      }
      // Numbers start from 0; Add 1 for readability
      std::cout << "Clause literal " << j + 1 << ":  " << true_literal << std::endl;
    }

    clause_index = SAT_GetNextClause(SAT_manager_, clause_index);
  }
}

void Game::PrintClauses() {
  for (std::vector<std::vector<int>>::size_type i = 0; i < var_mngr.clauses_.size(); ++i) {
    std::cout << "Clause No. " << i + 1 << std::endl;
    for (std::vector<int>::size_type j = 0; j < var_mngr.clauses_.size(); ++j) {
      std::cout << "Variable " << j + 1 << ": " << var_mngr.clauses_[i][j] << std::endl;
    }
  std::cout << std::endl;
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
      // std::cout << "\tValue Inserted" << std::endl;
    }
    if (SAT_GetVarAsgnment(SAT_manager_, i) == 0) {
      var_mngr.variable_list_[i-1].SetFinalValue(i * (-1));
      // std::cout << "\tValue Inserted" << std::endl;
    }
  }
  // DisplayClauses();
  GetClauses();
  PrintClauses();
  // DisplayResults(SAT_manager_, satisfiability_result_);
  // PrintSolution();
  InitialiseVariableShapes();
  InitialiseClauseShapes();
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
  std::cout << "...Game Over..." << std::endl;
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
  // every var got an assignment, no free variables left
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
      case sf::Event::Closed: // || sf::Keyboard::Keyboard::Escape:
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
  window_.draw(variable_text_);
  // window_.draw(variable_label_);

  for (int i = 0; i < num_variables_; ++i) {
    window_.draw(var_mngr.variable_list_[i].circle_);
    window_.draw(variable_label_[i]);
  }

  for (int j = 0; j < num_clauses_; ++j) {
    window_.draw(clause_string_[j]);
  }

  window_.display();
}

void Game::PrintSolution() {
  std::cout << std::endl;
  std::cout << "===== SOLUTION =====" << std::endl;

  if (satisfiability_result_ == UNSATISFIABLE) {
    std::cout << "No solution possible" << std::endl;
  } else {
    int s;

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
