// Copyright 2015, Aaron Ceross

#ifndef CLAUSE_OBJECT_HPP
#define CLAUSE_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class ClauseObject {
 public:
  ClauseObject();
  void SetClauseStrings(int num_clauses);
  void SetClauseLiterals();

  sf::CircleShape clause_value_;
  std::vector<sf::Text> clause_string_;
  std::vector<int> literals_;

};


#endif  // CLAUSE_OBJECT_HPP
