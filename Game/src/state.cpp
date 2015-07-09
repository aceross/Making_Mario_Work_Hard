// Copyright 2015, Aaron Ceross

#include "../include/state.hpp"
#include "../include/state_stack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures,
                        FontHolder& fonts, Player& player)
: window_(&window_)
, textures_(&textures)
, fonts_(&fonts_)
, player_(&player_)
{}

State::State(StateStack& states, Context context)
: states_(&states_)
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
