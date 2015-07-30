// Copyright 2015, Aaron Ceross

#include "../include/state_stack.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
: stack_()
, pending_list_()
, context_(context)
, factories_()
{}

void StateStack::Update(sf::Time delta_time) {
  // Iterate from top to bottom, stop as soon as update() returns false
  for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr) {
    if (!(*itr)->Update(delta_time)) { break; }
  }

  ApplyPendingChanges();
}

void StateStack::Draw() {
  // Draw all active states from bottom to top
  for (State::Ptr& state : stack_) {
    state->Draw();
  }
}

void StateStack::HandleEvent(const sf::Event& event) {
  // Iterate from top to bottom, stop as soon as handleEvent() returns false
  for (auto itr = stack_.rbegin(); itr != stack_.rend(); ++itr) {
    if (!(*itr)->HandleEvent(event)) { break; }
  }

  ApplyPendingChanges();
}

void StateStack::PushState(States::ID stateID) {
  pending_list_.push_back(PendingChange(Push, stateID));
}

void StateStack::PopState() {
  pending_list_.push_back(PendingChange(Pop));
}

void StateStack::ClearStates() {
  pending_list_.push_back(PendingChange(Clear));
}

bool StateStack::IsEmpty() const {
  return stack_.empty();
}

State::Ptr StateStack::CreateState(States::ID stateID) {
  auto found    = factories_.find(stateID);
  assert(found != factories_.end());

  return found->second();
}

void StateStack::ApplyPendingChanges() {
  for (PendingChange change : pending_list_) {
    switch (change.action) {
      case Push:
        stack_.push_back(CreateState(change.stateID));
        break;

      case Pop:
        stack_.pop_back();
        break;

      case Clear:
        stack_.clear();
        break;
    }
  }

  pending_list_.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{}
