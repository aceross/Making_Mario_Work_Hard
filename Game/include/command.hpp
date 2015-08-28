// Copyright 2015, Aaron Ceross

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

#include "category.hpp"


class SceneNode;

struct Command {
  typedef std::function<void(SceneNode&, sf::Time)> Action;

  Command();

  enum Location {
    StartGadget,
    Warp,
    VariableGadget,
    Clause,
    CheckIn,
    CheckOut,
    FinishGadget
  };

  Action action_;
  unsigned int category_;
  unsigned int location_;
  int var_assignment_;
  bool complemented_;
  bool gadget_finished_;
};

template <typename GameObject, typename Function>
Command::Action DerivedAction(Function fn)
{
  return [=] (SceneNode& node, sf::Time delta_time)
  {
    // Check if cast is safe
    assert(dynamic_cast<GameObject*>(&node) != nullptr);

    // Downcast node and invoke function on it
    fn(static_cast<GameObject&>(node), delta_time);
  };
}

#endif  // COMMAND_HPP
