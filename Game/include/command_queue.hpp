// Copyright 2015, Aaron Ceross

#ifndef COMMAND_QUEUE_HPP
#define COMMAND_QUEUE_HPP

#include <queue>
#include "command.hpp"

class CommandQueue {
 public:
  void    Push(const Command& command);
  Command Pop();
  bool    IsEmpty() const;

 private:
  std::queue<Command> queue_;
};

#endif  // COMMAND_QUEUE_HPP
