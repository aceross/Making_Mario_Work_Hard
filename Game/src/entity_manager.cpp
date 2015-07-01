// Copyright 2015, Aaron Ceross

#include <vector>
#include <string>
#include "../include/entity_manager.hpp"

EntityManager::EntityManager() {}

void EntityManager::Add(std::string name, Entity* entity) {
  std::unordered_map<std::string, Entity*>::const_iterator found =
                                                      this->entities.find(name);
  while (found != this->entities.end()) {
    name += "0";
    found = this->entities.find(name);
  }
  this->entities.insert(std::make_pair(name, entity));
}

Entity* EntityManager::Get(std::string name) {
  std::unordered_map<std::string, Entity*>::const_iterator found =
                                                      this->entities.find(name);
  if (found == this->entities.end()) {
    return NULL;
  } else {
    return found->second;
  }
}

bool EntityManager::Update(sf::RenderWindow* window) {
  std::vector<std::string> toRemove;

  for (auto& iterator : this->entities) {
    if (iterator.second->GroupID() > 2 || iterator.second->GroupID() == 1) {
      for (auto& iterator2 : this->entities) {
        if (iterator.first != iterator2.first) {
          if (iterator.second->Active() && iterator2.second->Active()) {
            if (iterator.second->CheckCollision(iterator2.second)) {
              iterator.second->Collision(iterator2.second);
            }
          }
        }
      }
    }

    switch (iterator.second->Active()) {
    case 0:
      toRemove.push_back(iterator.first);
      break;
    default:
      if (!iterator.second->Update(window)) { return false; }
      break;
    }
  }

  for (auto& iterator : toRemove) {
    std::unordered_map<std::string, Entity*>::const_iterator found =
                                                  this->entities.find(iterator);

    if (found != this->entities.end()) {
      delete found->second;
      this->entities.erase(iterator);
    }
  }
  toRemove.clear();

  return true;
}

void EntityManager::Render(sf::RenderWindow* window) {
  for (auto& iterator : this->entities) {
    window->draw(*iterator.second);
  }
}

EntityManager::~EntityManager() {
  for (auto& iterator : this->entities) {
    delete iterator.second;
  }
  this->entities.clear();
}
