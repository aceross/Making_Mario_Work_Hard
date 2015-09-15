// Copyright 2015, Aaron Ceross

#include <algorithm>
#include <stack>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../include/game_state_manager.hpp"
#include "../include/text_utility.hpp"
#include "../include/game_state.hpp"
#include "../include/state.hpp"
#include "../include/menu_state.hpp"
#include "../include/instance_selection.hpp"
#include "../include/pause_state.hpp"
#include "../include/input_state.hpp"
#include "../include/level.hpp"
#include "../include/title_screen_state.hpp"
#include "../include/state_identifiers.hpp"

const sf::Time GameStateManager::TimePerFrame = sf::seconds(1.f/35.f);

GameStateManager::GameStateManager()
: window_(sf::VideoMode(800, 600), "Making Mario Work Hard",
                                    sf::Style::Default)
, font_()
, textures_()
, player_manager_()
, mapfile_handler_()
, states_(State::Context(window_, textures_, font_, player_manager_, mapfile_handler_))
, stats_text_()
, stats_update_time_()
, stats_num_frames_(0)
, game_over_(false)
{
  window_.setKeyRepeatEnabled(false);
  window_.setVerticalSyncEnabled(true);

  font_.Load(Fonts::Main, "resources/font/OpenSans-Regular.ttf");
  font_.Load(Fonts::Title, "resources/font/FFF Zerofactor.ttf");

  textures_.Load(Textures::TitleScreen,  "resources/gfx/title_screen.png");
  textures_.Load(Textures::SelectScreen, "resources/gfx/select_screen.png");

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
  }
  std::cout << "Quitting the game..." << std::endl;
}

void GameStateManager::Render() {
  window_.clear(sf::Color::Blue);

  states_.Draw();

  window_.setView(window_.getDefaultView());
  window_.draw(stats_text_);
  window_.display();
}

// Information for checking that the frame rate is optimal
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
  states_.RegisterState<InstanceSelection>(States::Select);
  states_.RegisterState<InputState>(States::Input);
  states_.RegisterState<GameState>(States::Game);
  states_.RegisterState<PauseState>(States::Pause);
}

GameStateManager::~GameStateManager() {}
