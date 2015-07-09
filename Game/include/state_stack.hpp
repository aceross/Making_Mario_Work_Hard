// Copyright 2015, Aaron Ceross

#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include "state.hpp"
#include "resource_identifiers.hpp"
#include "state_identifiers.hpp"


namespace sf {
class Event;
class RenderWindow;
}

class StateStack : private sf::NonCopyable {
 public:
  enum Action { Push, Pop, Clear };

 public:
  explicit StateStack(State::Context context);

  template <typename T>
  void RegisterState(States::ID stateID);

  void Update(sf::Time dt);
  void Draw();
  void HandleEvent(const sf::Event& event);

  void PushState(States::ID stateID);
  void PopState();
  void ClearStates();

  bool IsEmpty() const;

 private:
  State::Ptr CreateState(States::ID stateID);
  void ApplyPendingChanges();

 private:
  struct PendingChange {
    explicit PendingChange(Action action, States::ID stateID = States::None);
    Action     action;
    States::ID stateID;
  };

 private:
  std::vector<State::Ptr> stack_;
  std::vector<PendingChange> pending_list_;

  State::Context context_;
  std::map<States::ID, std::function<State::Ptr()>> factories_;
};


template <typename T>
void StateStack::RegisterState(States::ID stateID) {
  factories_[stateID] = [this] () {
    return State::Ptr(new T(*this, context_));
  };
}

#endif  // STATE_STACK_HPP
