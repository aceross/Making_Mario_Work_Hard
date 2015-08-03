// Copyright 2015, Aaron Ceross

#include <map>
#include <string>
#include <algorithm>

#include "../include/player_manager.hpp"
#include "../include/command_queue.hpp"
#include "../include/player.hpp"

using namespace std::placeholders;

struct PlayerMover {
  PlayerMover(float vx, float vy)
  : velocity(vx, vy)
  {}

  void operator() (Player& player, sf::Time) const {
    // player.accelerate(velocity * player.getMaxSpeed());
  }

  sf::Vector2f velocity;
};

PlayerManager::PlayerManager()
: current_level_status_(LevelRunning)
{
  // Set initial key bindings
  key_binding_[sf::Keyboard::Left]  = MoveLeft;
  key_binding_[sf::Keyboard::Right] = MoveRight;
  key_binding_[sf::Keyboard::Space] = Jump;
  key_binding_[sf::Keyboard::Down]  = Crouch;

  // Set initial action bindings
  InitialiseActions();

  // Assign all categories to player's aircraft
  for (auto& pair : action_binding_)
    pair.second.category_ = Category::Player;
}

void PlayerManager::HandleEvent(const sf::Event& event,
                                      CommandQueue& commands) {
  if (event.type == sf::Event::KeyPressed) {
    // Check if pressed key appears in key binding, trigger command if so
    auto found = key_binding_.find(event.key.code);
    if (found != key_binding_.end() && !IsRealtimeAction(found->second))
      commands.Push(action_binding_[found->second]);
  }
}

void PlayerManager::HandleRealtimeInput(CommandQueue& commands) {
  // Traverse all assigned keys and check if they are pressed
  for (auto pair : key_binding_) {
    // If key is pressed, lookup action and trigger corresponding command
    if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
      commands.Push(action_binding_[pair.second]);
  }
}

void PlayerManager::AssignKey(Action action, sf::Keyboard::Key key) {
  // Remove all keys that already map to action
  for (auto itr = key_binding_.begin(); itr != key_binding_.end(); ) {
    if (itr->second == action)
      key_binding_.erase(itr++);
    else
      ++itr;
  }
  // Insert new binding
  key_binding_[key] = action;
}

sf::Keyboard::Key PlayerManager::GetAssignedKey(Action action) const {
  for (auto pair : key_binding_) {
    if (pair.second == action) {
      return pair.first;
    }
  }
  return sf::Keyboard::Unknown;
}

void PlayerManager::SetLevelStatus(LevelStatus status) {
  current_level_status_ = status;
}

PlayerManager::LevelStatus PlayerManager::GetLevelStatus() const {
  return current_level_status_;
}

void PlayerManager::InitialiseActions() {
  action_binding_[MoveLeft].action_  = DerivedAction<Player>(PlayerMover(-1, 0));
  action_binding_[MoveRight].action_ = DerivedAction<Player>(PlayerMover(+1, 0));
  action_binding_[Jump].action_      = DerivedAction<Player>(PlayerMover(0, -1));
  action_binding_[Crouch].action_    = DerivedAction<Player>(PlayerMover(0, +1));
}

bool PlayerManager::IsRealtimeAction(Action action) {
  switch (action) {
    case MoveLeft:
    case MoveRight:
    case Crouch:
    case Jump:
      return true;

    default:
      return false;
  }
}
