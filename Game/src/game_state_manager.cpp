// Copyright 2015, Aaron Ceross

#include <algorithm>
#include <stack>
#include <iostream>
#include <string>

#include "../include/game_state_manager.hpp"
#include "../include/text_utility.hpp"
#include "../include/game_state.hpp"
#include "../include/state.hpp"
#include "../include/menu_state.hpp"
#include "../include/pause_state.hpp"
#include "../include/level.hpp"
#include "../include/title_screen_state.hpp"
#include "../include/state_identifiers.hpp"

const sf::Time GameStateManager::TimePerFrame = sf::seconds(1.f/60.f);

// GSM contructor initialises the font, texture
GameStateManager::GameStateManager()
: window_(sf::VideoMode(800, 600), "Making Mario Work Hard",
                                    sf::Style::Default)
, font_()
, textures_()
, player_manager_()
, states_(State::Context(window_, textures_, font_, player_manager_))
, stats_text_()
, stats_update_time_()
, stats_num_frames_(0)
{
  window_.setKeyRepeatEnabled(false);
  window_.setVerticalSyncEnabled(true);

  font_.Load(Fonts::Main, "resources/font/Fixedsys500c.ttf");

  stats_text_.setFont(font_.Get(Fonts::Main));
  stats_text_.setPosition(5.f, 5.f);
  stats_text_.setCharacterSize(10u);

  RegisterStates();
  states_.PushState(States::Title);
}

void GameStateManager::Run() {
  sf::Clock update_clock;
  sf::Time time_since_last_update = sf::Time::Zero;

  while (window_.isOpen() && !game_over_) {
    // Determine the time that passed
    // add up previous leftover time
    sf::Time delta_time     = update_clock.restart();
    time_since_last_update += delta_time;

    while (time_since_last_update > TimePerFrame) {
      time_since_last_update -= TimePerFrame;
      ProcessInputs();
      Update(TimePerFrame);
      if (states_.IsEmpty()) { window_.close(); }
    }

    UpdateStatistics(delta_time);
    Render();
    // sf::sleep(sf::microseconds(1));
  }
  std::cout << "Quitting the game..." << std::endl;
}

void GameStateManager::Render() {
  window_.clear();

  states_.Draw();

  window_.setView(window_.getDefaultView());
  window_.draw(stats_text_);
  window_.display();
}

void GameStateManager::UpdateStatistics(sf::Time delta_time) {
  stats_update_time_ += delta_time;
  stats_num_frames_  += 1;

  if (stats_update_time_ >= sf::seconds(1.0f)) {
    stats_text_.setString(
      "Frames / Second = " + std::to_string(stats_num_frames_) + "\n" +
      "Time / Update = "  + std::to_string(stats_update_time_.asMicroseconds() /
                                           stats_num_frames_) + "us");
    stats_text_.setPosition(10.f, 575.f);
  }

}

void GameStateManager::ProcessInputs() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    states_.HandleEvent(event);

    if (event.type == sf::Event::Closed)
      window_.close();
  }
}

void GameStateManager::Update(sf::Time delta_time) {
  states_.Update(delta_time);
}

void GameStateManager::RegisterStates() {
  states_.RegisterState<TitleScreenState>(States::Title);
  states_.RegisterState<MenuState>(States::Menu);
  states_.RegisterState<GameState>(States::Game);
  states_.RegisterState<PauseState>(States::Pause);
}

GameStateManager::~GameStateManager() {
  // while (!states_.empty()) popState();
}
