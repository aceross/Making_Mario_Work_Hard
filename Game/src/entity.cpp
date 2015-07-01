// Copyright 2015, Aaron Ceross

#include <string>
#include "../include/entity.hpp"

sf::Vector2f Entity::scroll(0, 0);

Entity::Entity() {
  this->texture = new sf::Texture();
  this->active  = 1;
  this->groupId = 0;
}

void Entity::Load(std::string filename) {
  this->texture->loadFromFile("Graphics/sprites/" + filename);
  this->setTexture(*this->texture);
}

bool Entity::Update(sf::RenderWindow* window) {
  this->move(this->velocity);
  return true;
}

void Entity::Collision(Entity* entity) {}

bool Entity::CheckCollision(Entity* entity) {
  return this->getGlobalBounds().intersects(entity->getGlobalBounds());
}

int Entity::GroupID() { return this->groupId; }

int Entity::Active() { return this->active; }

void Entity::Destroy() {
  this->active = 0;
}

Entity::~Entity() {
  delete this->texture;
}
