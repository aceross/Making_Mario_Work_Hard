// Copyright 2015, Aaron Ceross

#include <map>
#include <string>
#include <algorithm>

#include "../include/player.hpp"
#include "../include/command_queue.hpp"

using namespace std::placeholders;

struct AircraftMover {
  AircraftMover(float vx, float vy)
  : velocity(vx, vy)
  {}

  void operator() (Aircraft& aircraft, sf::Time) const {
    aircraft.accelerate(velocity * aircraft.getMaxSpeed());
  }

  sf::Vector2f velocity;
};

Player::Player()
: current_mission_status_(MissionRunning)
{
  // Set initial key bindings
  key_binding_[sf::Keyboard::Left]  = MoveLeft;
  key_binding_[sf::Keyboard::Right] = MoveRight;
  key_binding_[sf::Keyboard::Up]    = MoveUp;
  key_binding_[sf::Keyboard::Down]  = MoveDown;
  key_binding_[sf::Keyboard::Space] = Fire;
  key_binding_[sf::Keyboard::M]     = LaunchMissile;

  // Set initial action bindings
  InitialiseActions();

  // Assign all categories to player's aircraft
  for (auto& pair : action_binding_)
    pair.second.category_ = Category::PlayerAircraft;
}

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands) {
  if (event.type == sf::Event::KeyPressed) {
    // Check if pressed key appears in key binding, trigger command if so
    auto found = key_binding_.find(event.key.code);
    if (found != key_binding_.end() && !IsRealtimeAction(found->second))
      commands.Push(action_binding_[found->second]);
  }
}

void Player::HandleRealtimeInput(CommandQueue& commands) {
  // Traverse all assigned keys and check if they are pressed
  for (auto pair : key_binding_) {
    // If key is pressed, lookup action and trigger corresponding command
    if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
      commands.Push(action_binding_[pair.second]);
  }
}

void Player::AssignKey(Action action, sf::Keyboard::Key key) {
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

sf::Keyboard::Key Player::GetAssignedKey(Action action) const {
  for (auto pair : key_binding_) {
    if (pair.second == action) {
      return pair.first;
    }
  }
  return sf::Keyboard::Unknown;
}

void Player::SetMissionStatus(MissionStatus status) {
  current_mission_status_ = status;
}

Player::MissionStatus Player::GetMissionStatus() const {
  return current_mission_status_;
}

void Player::InitialiseActions() {
  key_binding_[MoveLeft].action  = derivedAction<Aircraft>(AircraftMover(-1, 0));
  key_binding_[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+1, 0));
  key_binding_[MoveUp].action    = derivedAction<Aircraft>(AircraftMover(0, -1));
  key_binding_[MoveDown].action  = derivedAction<Aircraft>(AircraftMover(0, +1));
  key_binding_[Fire].action      = derivedAction<Aircraft>([] (Aircraft& a, sf::Time){ a.fire(); });
  key_binding_[LaunchMissile].action =
      derivedAction<Aircraft>([] (Aircraft& a, sf::Time){ a.launchMissile(); });
}

bool Player::IsRealtimeAction(Action action) {
  switch (action) {
    case MoveLeft:
    case MoveRight:
    case MoveDown:
    case MoveUp:
    case Fire:
      return true;

    default:
      return false;
  }
}
