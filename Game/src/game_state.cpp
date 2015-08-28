// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>
#include "../include/game_state.hpp"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, level_(*context.window_, *context.fonts_)
, player_manager_(*context.player_manager_)
{
  player_manager_.SetLevelStatus(PlayerManager::LevelRunning);

  player_manager_.SetTileMap(level_.GetTileMap());
  player_manager_.SetVariableManager(level_.GetVarManager());
  std::cout << "TileMap set in player_manager" << std::endl;

  // Set Solition queue
  CommandQueue& commands = level_.GetCommandQueue();
  player_manager_.SetSolutionQueue(commands);

  // music goes here if needed
}

void GameState::Draw() {
  level_.draw();
}

bool GameState::Update(sf::Time delta_time) {
  level_.Update(delta_time);

  CommandQueue& commands = level_.GetCommandQueue();
  player_manager_.HandleRealtimeInput(commands);

  return true;
}

bool GameState::HandleEvent(const sf::Event &event) {
  // Game input handling
  CommandQueue& commands = level_.GetCommandQueue();
  player_manager_.HandleEvent(event, commands);

  // Escape pressed, trigger the pause screen
  if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) {
    RequestStackPush(States::Pause);
  }

  // HandleInput(event);
  return true;
}
