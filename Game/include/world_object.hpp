// // Copyright 2015, Aaron Ceross
//
// #ifndef WORLD_OBJECT_HPP
// #define WORLD_OBJECT_HPP
//
// #include "entity.hpp"
// #include "resource_identifiers.hpp"
//
// class WorldObject : public Entity {
// public:
//  enum Type { Koopa, Brick, TypeCount };
//
// public:
//  WorldObject(Type type, const TextureHolder& textures, const FontHolder& fonts);
//
//  virtual unsigned int  GetCategory() const;
//  virtual sf::FloatRect GetBoundingRect() const;
//
// private:
//  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
//  virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);
//
// };
//
// #endif  // WORLD_OBJECT_HPP
