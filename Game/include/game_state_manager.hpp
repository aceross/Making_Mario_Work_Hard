// Copyright 2015, Aaron Ceross

#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <stack>
#include <map>
#include <string>

#include "resource_manager.hpp"
#include "resource_identifiers.hpp"
#include "state_stack.hpp"
#include "player_manager.hpp"
#include "../lib/zchaff/SAT.h"

// Values for the game window
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class GameStateManager {
// Methods
 private:
  void Update(sf::Time delta_time);
  void ProcessInputs();
  void Render();

  void UpdateStatistics(sf::Time delta_time);

  void RegisterStates();

// member variables
 private:
  sf::RenderWindow    window_;
  sf::ContextSettings settings_;

  FontHolder    font_;
  TextureHolder textures_;

  PlayerManager player_manager_;
  StateStack    states_;

  sf::Text    stats_text_;
  sf::Time    stats_update_time_;
  std::size_t stats_num_frames_;

  static const sf::Time TimePerFrame;
  static const int tileSize = 32;
  bool game_over_           = false;

 private:
  // SAT_Manager sat_manager_;

 public:
  GameStateManager();
  ~GameStateManager();

  void Run();
};

#endif  // GAME_STATE_MANAGER_HPP
