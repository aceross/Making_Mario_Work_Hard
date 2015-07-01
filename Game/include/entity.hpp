// Copyright 2015, Aaron Ceross

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
 public:
  sf::Vector2f velocity;
  static sf::Vector2f scroll;

  Entity();

  void Load(std::string filename);

  virtual bool Update(sf::RenderWindow* window);

  bool CheckCollision(Entity* entity);

  virtual void Collision(Entity* entity);

  int GroupID();

  int Active();

  void Destroy();

  ~Entity();

 protected:
  int active;
  int groupId;

 private:
  sf::Texture* texture;
};

#endif  // ENTITY_HPP
