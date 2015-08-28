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
{
  std::cout << "Setting intitial key bindings" << std::endl;
  // Set initial key bindings
  key_binding_[sf::Keyboard::Left]  = MoveLeft;
  key_binding_[sf::Keyboard::Right] = MoveRight;
  key_binding_[sf::Keyboard::Space] = Jump;

  // Set initial action bindings
  InitialiseActions();

  // Assign all categories to player
  for (auto& pair : action_binding_) {
    pair.second.category_ = Category::MarioPlayer;
  }

  // Set solution queue initialisation
  // SetSolutionQueue();
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
}

bool PlayerManager::IsRealtimeAction(Action action) {
  switch (action) {
    case MoveLeft:
    case MoveRight:
    case Jump:
      return true;

    default:
      return false;
  }
}

void PlayerManager::SetTileMap(TileMap tm) {
  tile_map_ = tm;
}

void PlayerManager::SetVariableManager(VariableManager var_manager) {
  var_manager_ = var_manager;
}

void PlayerManager::SetSolutionQueue(CommandQueue& commands) {
  InitStartQueue(commands);
}

void PlayerManager::InitStartQueue(CommandQueue& commands) {
  // 1 tile move = 8 moves e.g. 8 tiles = 64 moves
  for (int i = 0; i < 64; ++i) {
    commands.Push(action_binding_[MoveRight]);
  }
}
