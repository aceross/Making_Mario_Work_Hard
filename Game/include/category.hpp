// Copyright 2015, Aaron Ceross

#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Entity/scene node category, used to dispatch commands
namespace Category {
  enum Type {
    None           = 0,
    Scene          = 1 << 0,
    Player         = 1 << 1,
    AlliedAircraft = 1 << 2,
    Enemy          = 1 << 3,
  };
}

#endif  // CATEGORY_HPP
