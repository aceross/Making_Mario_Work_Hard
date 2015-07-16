// Copyright 2015, Aaron Ceross

#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>

#include "command.hpp"
#include "command_queue.hpp"
#include "resource_identifiers.hpp"
#include "text_node.hpp"
#include "entity.hpp"

class CommandQueue;

class PlayerManager : public Entity {
 public:
  enum Action {
    MoveLeft,
    MoveRight,
    Jump,
    Crouch,
    Fire,
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

 public:
  virtual sf::FloatRect GetBoundingRect() const;

 private:
  void InitialiseActions();
  static bool IsRealtimeAction(Action action);

 private:
  virtual void DrawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const;
  virtual void UpdateCurrent(sf::Time delta_time_, CommandQueue& commands);
  void UpdateText();

 private:
  std::map<sf::Keyboard::Key, Action> key_binding_;
  std::map<Action, Command>           action_binding_;
  LevelStatus                         current_level_status_;
};

#endif  // PLAYER_MANAGER_HPP
