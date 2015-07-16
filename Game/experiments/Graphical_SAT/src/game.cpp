// Copyright 2015, Aaron Ceross

#include <string>
#include <set>
#include <vector>

#include "../include/game.hpp"

Game::Game() {
  InitialiseWindow();
  LoadAssets();
  SAT_manager_ = SAT_InitManager();
  ReadFile();
}

void Game::InitialiseWindow() {
  settings_.antialiasingLevel = 8;
  window_.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                               "Graphical SAT Solver",
                                sf::Style::Default, settings_);
  window_.setFramerateLimit(60);
}

void Game::LoadAssets() {
  // Load the welcome text
  if (!font_.loadFromFile("font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  welcome_text_.setFont(font_);
  welcome_text_.setColor(sf::Color::White);
  welcome_text_.setString("Graphical SAT Solver");
  welcome_text_.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void Game::ReadFile() {
  std::cout <<"Reading CNF file... "<< std::endl;

  char line_buffer[MAX_LINE_LENGTH];
  char word_buffer[MAX_WORD_LENGTH];
  std::set<int> clause_vars;
  std::set<int> clause_lits;
  int line_num = 0;

  std::string filename = "lib/zchaff/quinn.cnf";

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
      if ( arg < 2 ) {
        std::cerr << "Unable to read number of variables and clauses"
                  << "at line " << line_num << std::endl;
        exit(3);
      }
      SAT_SetNumVariables(SAT_manager_, var_num);  // first element not used.
    } else {                              // Clause definition or continuation
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
            if (var_idx < 0)  { var_idx = -var_idx; sign = 1; }
            clause_vars.insert(var_idx);
            clause_lits.insert((var_idx << 1) + sign);
          } else {
              // add this clause
              if (clause_vars.size() != 0 &&
                 (clause_vars.size() == clause_lits.size())) {
                // yeah, can add this clause
                std::vector<int> temp;
                for (std::set<int>::iterator itr = clause_lits.begin();
                     itr != clause_lits.end(); ++itr) {
                  temp.push_back(*itr);
                SAT_AddClause(SAT_manager_, & temp.begin()[0], temp.size());
                }
              // it contain var of both polarity, so is automatically satisfied
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
    std::cerr << "Input line " << line_num
              <<  " too long. Unable to continue..." << std::endl;
    exit(2);
  }
  // assert (clause_vars.size() == 0);
  // some benchmark has no 0 in the last clause
  if (clause_lits.size() && clause_vars.size() == clause_lits.size()) {
    std::vector <int> temp;
    for (std::set<int>::iterator itr = clause_lits.begin();
         itr != clause_lits.end(); ++itr) {
      temp.push_back(*itr);
    }
    SAT_AddClause(SAT_manager_, & temp.begin()[0], temp.size());
  }
  clause_lits.clear();
  clause_vars.clear();
  std::cout <<"Finished reading CNF file..."<< std::endl;
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
  window_.clear(sf::Color::Black);
  window_.draw(welcome_text_);
  window_.display();
}

void Game::Run() {
  while (window_.isOpen()) {
    HandleEvents();
    Draw();
  }
}

Game::~Game() {}
