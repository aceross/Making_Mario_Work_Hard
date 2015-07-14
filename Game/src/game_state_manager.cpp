// Copyright 2015, Aaron Ceross

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <algorithm>
#include <stack>
#include <iostream>

#include "../include/game_state_manager.hpp"
#include "../include/game_state.hpp"
#include "../include/menu_state.hpp"
#include "../include/pause_state.hpp"
#include "../include/level_state.hpp"
#include "../include/title_screen_state.hpp"
#include "../include/state_identifiers.hpp"

const sf::Time GameStateManager::TimePerFrame = sf::seconds(1.f/60.f);

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
    sf::sleep(sf::microseconds(1));
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
      "Frames / Second = " + toString(stats_num_frames_) + "\n" +
      "Time / Update = "   + toString(stats_update_time_.asMicroseconds() /
                                      stats_num_frames_) + "us");
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

GameStateManager::GameStateManager()
: settings_.antialiasingLevel(8)
, window_(sf::VideoMode(800, 600), "Making Mario Work Hard",
                                    sf::Style::Default, settings_)
, font_();
, player_();
, states_(State::Context(window_, font_, player_))
, stats_text_()
, stats_update_time_()
, stats_num_frames_(0)
{
  window_.setKeyRepeatEnabled(false);

  font_.load(Fonts::Main, "resources/font/OpenSans-Regular.ttf");
  stats_text_.setFont(font_.get(Fonts::Main));
  stats_text_.setPosition(5.f, 5.f);
  stats_text_.setCharacterSize(10u);
}

void GameStateManager::RegisterStates() {
  states_.RegisterState<TitleScreenState>(States::Title);
  states_.RegisterState<MenuState>(States::Menu);
  states_.RegisterState<LevelState>(States::Level);
  states_.RegisterState<PauseState>(States::Pause);
}

GameStateManager::~GameStateManager() {
  // while (!states_.empty()) popState();
}
