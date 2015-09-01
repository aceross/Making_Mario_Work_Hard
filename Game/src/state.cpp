// Copyright 2015, Aaron Ceross

#include "../include/state.hpp"
#include "../include/state_stack.hpp"
#include "../include/player_manager.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
                        FontHolder& fonts, PlayerManager& player_manager,
                        MapfileHandler& mapfile_handler)
: window_(&window)
, textures_(&textures)
, fonts_(&fonts)
, player_manager_(&player_manager)
, mapfile_handler_(&mapfile_handler)
{}

State::State(StateStack& states, Context context)
: states_(&states)
, context_(context)
{}

State::~State() {}

void State::RequestStackPush(States::ID stateID) {
  states_->PushState(stateID);
}

void State::RequestStackPop() {
  states_->PopState();
}

void State::RequestStateClear() {
  states_->ClearStates();
}

State::Context State::GetContext() const {
  return context_;
}

void State::SetMapfile(std::string mapfile) {
  context_.mapfile_handler_->SetMapfile(mapfile);
}
