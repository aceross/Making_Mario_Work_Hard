// Copyright 2015, Aaron Ceross

#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <SFML/Window/Event.hpp>
#include <map>
#include <queue>
#include "command.hpp"
#include "tile_map.hpp"
#include "navigation_manager.hpp"
#include "variable_manager.hpp"

class CommandQueue;

class PlayerManager {
 public:
  enum Action {
    MoveLeft,
    MoveRight,
    Jump,
    Down,
    Wait,
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

  void SetLevelStatus(LevelStatus status);
  LevelStatus GetLevelStatus() const;

  void SetTileMap(TileMap tm);
  void SetSolutionQueue(CommandQueue& commands);
  void SetVariableManager(VariableManager var_manager);
 // public:
 //  virtual sf::FloatRect GetBoundingRect() const;

 private:
  void InitialiseActions();
  static bool IsRealtimeAction(Action action);

 private:
  void SetVariableAssignments();
  void SetAssignmentLocation(int current_var);
  void InitStartQueue(CommandQueue& commands);
  void InitVariableQueue(CommandQueue& commands);
  void InitWarpQueue(CommandQueue& commands);
  void WarpAction(CommandQueue& commands);
  void InitClauseQueue(CommandQueue& commands);
  void InitCheckInQueue(CommandQueue& commands);
  void InitCheckoutQueue(CommandQueue& commands);
  void InitFinishQueue(CommandQueue& commands);

  void PrintLocation();

 private:
  std::map<sf::Keyboard::Key, Action> key_binding_;
  std::map<Action, Command>           action_binding_;
  LevelStatus                         current_level_status_;

  TileMap           tile_map_;
  VariableManager   var_manager_;
  NavigationManager navigation_manager_;
  std::queue<int>   assigned_variables_;
  int               current_variable_;
  std::vector< std::vector<int> > location_map_;

private:
  // location boolean values
  bool in_start_gadget_;
  bool in_variable_gadget_;
  bool in_warp_gadget_;
  bool finished_warps_;
  bool no_warp_gadgets_;
  bool in_check_in_;
  bool in_clause_gadget_;
  bool in_check_out_;
  bool in_finish_;
};

#endif  // PLAYER_MANAGER_HPP
