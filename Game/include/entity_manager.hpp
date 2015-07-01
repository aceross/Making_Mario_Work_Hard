// Copyright 2015, Aaron Ceross

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <string>
#include "entity.hpp"

class EntityManager {
 public:
  EntityManager();
  ~EntityManager();

  void Add(std::string name, Entity* entity);
  Entity* Get(std::string name);

  bool Update(sf::RenderWindow* window);
  void Render(sf::RenderWindow* window);

 private:
  std::unordered_map<std::string, Entity*> entities;
};

#endif  // ENTITY_MANAGER_HPP
