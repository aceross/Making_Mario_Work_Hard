// Copyright 2015, Aaron Ceross

#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "entity.hpp"

class WorldObject : public Entity {
public:
 enum Type {
   Wall,
   QuestionBox,
   VariablePipe,
   Warp,
   WarpExit,
   BreakBrick,
   Metal,
   TypeCount
 };

};

#endif  // WORLD_OBJECT_HPP
