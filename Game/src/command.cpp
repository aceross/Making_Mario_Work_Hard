// Copyright 2015, Aaron Ceross

#include "../include/command.hpp"

Command::Command()
: action_()
, category_(Category::None)
, location_(0)
, var_assignment_(0)
, complemented_(false)
, gadget_finished_(false)
{}
