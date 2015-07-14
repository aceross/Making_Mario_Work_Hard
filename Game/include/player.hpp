// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <map>
#include "command.hpp"

class CommandQueue;

class Player {
 public:
  enum Action {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Fire,
    LaunchMissile,
    ActionCount
  };

  enum MissionStatus {
    MissionRunning,
    MissionSuccess,
    MissionFailure
  };

 public:
  Player();
  void HandleEvent(const sf::Event& event, CommandQueue& commands);
  void HandleRealtimeInput(CommandQueue& commands);

  void AssignKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key GetAssignedKey(Action action) const;

  void SetMissionStatus(MissionStatus status);
  MissionStatus GetMissionStatus() const;

 private:
  void InitialiseActions();
  static bool IsRealtimeAction(Action action);

 private:
  std::map<sf::Keyboard::Key, Action> key_binding_;
  std::map<Action, Command>           action_binding_;
  MissionStatus                       current_mission_status_;
};

#endif // BOOK_PLAYER_HPP
