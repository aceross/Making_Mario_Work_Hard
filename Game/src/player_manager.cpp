// Copyright 2015, Aaron Ceross

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

#include "../include/player_manager.hpp"
#include "../include/command_queue.hpp"
#include "../include/mario.hpp"

using namespace std::placeholders;

struct MarioMover {
  MarioMover(float vx, float vy)
  : location_update(vx, vy)
  {}

  void operator() (Mario& mario, sf::Time) const {
    mario.move(location_update);
  }

  sf::Vector2f location_update;
};

PlayerManager::PlayerManager()
: current_level_status_(LevelRunning)
, in_start_gadget_(true)
, in_variable_gadget_(false)
{
  std::cout << "Setting intitial key bindings" << std::endl;
  // Set initial key bindings
  key_binding_[sf::Keyboard::Left]  = MoveLeft;
  key_binding_[sf::Keyboard::Right] = MoveRight;
  key_binding_[sf::Keyboard::Space] = Jump;
  key_binding_[sf::Keyboard::Down]  = Down;

  // Set initial action bindings
  InitialiseActions();

  // Assign all categories to player
  for (auto& pair : action_binding_) {
    pair.second.category_ = Category::MarioPlayer;
  }
}

void PlayerManager::SetVariableManager(VariableManager var_manager) {
  var_manager_ = var_manager;
}

void PlayerManager::SetVariableAssignments() {
  unsigned int variables = var_manager_.GetNumVariables();
  int temp;

  for (int i = 0; i < variables; ++i) {
    temp = var_manager_.variable_list_[i].GetFinalValue();
    assigned_variables_.push(temp);
  }

  // test
  // for (int i = 0; i < variables; ++i) {
  //   temp = assigned_variables_.front();
  //   std::cout << "Final Variable " << i + 1 << ": " << temp << std::endl;
  //   assigned_variables_.pop();
  // }

}

void PlayerManager::SetTileMap(TileMap tm) {
  tile_map_ = tm;
}

void PlayerManager::HandleEvent(const sf::Event& event,
                                      CommandQueue& commands) {
  if (event.type == sf::Event::KeyPressed) {
    // Check if pressed key appears in key binding, trigger command if so
    auto found = key_binding_.find(event.key.code);
    if (found != key_binding_.end() && !IsRealtimeAction(found->second)) {
      commands.Push(action_binding_[found->second]);
    }
  }
}

void PlayerManager::HandleRealtimeInput(CommandQueue& commands) {
  // // Traverse all assigned keys and check if they are pressed
  for (auto pair : key_binding_) {
    // If key is pressed, lookup action and trigger corresponding command
    if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second)) {
      // std::cout << "Pushing Real Time Input" << std::endl;
      commands.Push(action_binding_[pair.second]);
    }
  }
}

void PlayerManager::SetLevelStatus(LevelStatus status) {
  current_level_status_ = status;
}

PlayerManager::LevelStatus PlayerManager::GetLevelStatus() const {
  return current_level_status_;
}

void PlayerManager::InitialiseActions() {
  const float location_update = 2.f;
  action_binding_[MoveLeft].action_  = DerivedAction<Mario>(MarioMover(-location_update, 0));
  action_binding_[MoveRight].action_ = DerivedAction<Mario>(MarioMover(+location_update, 0));
  action_binding_[Jump].action_      = DerivedAction<Mario>(MarioMover(0, -location_update));
  action_binding_[Down].action_      = DerivedAction<Mario>(MarioMover(0, +16));
}

bool PlayerManager::IsRealtimeAction(Action action) {
  switch (action) {
    case MoveLeft:
    case MoveRight:
    case Jump:
    case Down:
      return true;

    default:
      return false;
  }
}

void PlayerManager::SetSolutionQueue(CommandQueue& commands) {
  // Set solution queue initialisation
  SetVariableAssignments();

  InitStartQueue(commands);
}

void PlayerManager::InitStartQueue(CommandQueue& commands) {
  current_variable_ = assigned_variables_.front();
  assigned_variables_.pop();

  // 1 tile move = 8 moves e.g. 8 tiles = 64 moves
  for (int i = 0; i < 112; ++i) {
    Command c = action_binding_[MoveRight];
    c.location_       = c.StartGadget;
    c.var_assignment_ = current_variable_;
    commands.Push(c);
  }

  // some kind of jump
  for (int j = 0; j < 2; ++ j) {
    Command c = action_binding_[Down];
    c.location_       = c.StartGadget;
    c.var_assignment_ = current_variable_;
    commands.Push(c);
  }

  // Select the path based on the variable assignment
  if (current_variable_ < 0) {
    for (int i = 0; i < 24; ++i) {
      Command c = action_binding_[MoveRight];
      c.location_       = c.StartGadget;
      c.var_assignment_ = current_variable_;
      commands.Push(c);
    }
  } else {
    for (int i = 0; i < 24; ++i) {
      Command c         = action_binding_[MoveLeft];
      c.location_       = c.StartGadget;
      c.var_assignment_ = current_variable_;
      commands.Push(c);
    }
  }

  // fall
  for (int j = 0; j < 4; ++ j) {
    Command c         = action_binding_[Down];
    c.location_       = c.StartGadget;
    c.var_assignment_ = current_variable_;
    commands.Push(c);
  }

  InitWarpQueue(commands);
  //
  // int var = var_manager_.GetNumVariables();
  // for (int i = 0; i < var - 1; ++i) {
  InitVariableQueue(commands);
  InitVariableQueue(commands);
  // InitCheckInQueue(commands);
  // }
}

void PlayerManager::InitWarpQueue(CommandQueue& commands) {
  // 1 tile move = 8 moves e.g. 8 tiles = 64 moves
  for (int i = 0; i < 112; ++i) {
    Command c = action_binding_[MoveRight];
    c.location_       = c.Warp;
    c.var_assignment_ = current_variable_;
    commands.Push(c);
  }
}

void PlayerManager::InitVariableQueue(CommandQueue& commands) {
  current_variable_ = assigned_variables_.front();
  assigned_variables_.pop();

  // 1 tile move = 8 moves e.g. 8 tiles = 64 moves
  // for (int i = 0; i < 25; ++i) {
    Command c = action_binding_[MoveRight];
    c.location_       = c.VariableGadget;
    c.var_assignment_ = current_variable_;
    commands.Push(c);
  // }

}

void PlayerManager::InitCheckInQueue(CommandQueue &commands) {
  Command c         = action_binding_[Jump];
  c.location_       = c.CheckIn;
  // c.var_assignment_ = current_variable_;
  commands.Push(c);
}
