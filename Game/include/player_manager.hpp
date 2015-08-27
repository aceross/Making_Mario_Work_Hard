// Copyright 2015, Aaron Ceross

#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <SFML/Window/Event.hpp>
#include <map>
#include "command.hpp"
#include "tile_map.hpp"

class CommandQueue;

class PlayerManager {
 public:
  enum Action {
    MoveLeft,
    MoveRight,
    Jump,
    ActionCount
  };

  enum LevelStatus {
    LevelRunning,
    LevelSuccess,
    LevelFailure
  };

 public:
  PlayerManager();
  void HandleEvent(const sf::Event& event, CommandQueue& commands);
  void HandleRealtimeInput(CommandQueue& commands);

  void AssignKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key GetAssignedKey(Action action) const;

  void SetLevelStatus(LevelStatus status);
  LevelStatus GetLevelStatus() const;

  void SetTileMap(TileMap tm);
 // public:
 //  virtual sf::FloatRect GetBoundingRect() const;

 private:
  void InitialiseActions();
  static bool IsRealtimeAction(Action action);


 private:
  void InitialiseQueues();
  void InitStartQueue();
  void InitVariableQueue();
  void InitWarpQueue();
  void InitClauseQueue();
  void InitCheckInQueue();
  void InitCheckoutQueue();
  void InitFinishQueue();

 private:
  std::map<sf::Keyboard::Key, Action> key_binding_;
  std::map<Action, Command>           action_binding_;
  LevelStatus                         current_level_status_;

  TileMap tile_map_;
};

#endif  // PLAYER_MANAGER_HPP