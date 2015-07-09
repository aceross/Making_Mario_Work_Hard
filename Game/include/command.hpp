// Copyright 2015, Aaron Ceross

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

#include "category.hpp"


class SceneNode;

struct Command {
  Command();

  std::function<void(SceneNode&, sf::Time)> action_;
  unsigned int category_;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
  return [=] (SceneNode& node, sf::Time delta_time)
  {
    // Check if cast is safe
    assert(dynamic_cast<GameObject*>(&node) != nullptr);

    // Downcast node and invoke function on it
    fn(static_cast<GameObject&>(node), delta_time);
  };
}

#endif // BOOK_COMMAND_HPP
