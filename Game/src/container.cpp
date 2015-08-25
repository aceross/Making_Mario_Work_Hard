// Copyright 2015, Aaron Ceross

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../include/container.hpp"

namespace GUI {

Container::Container()
: children_()
, selected_child_(-1)
{}

void Container::Pack(Component::Ptr component) {
  children_.push_back(component);

  if (!HasSelection() && component->IsSelectable()) {
    Select(children_.size() - 1);
  }
}

bool Container::IsSelectable() const {
  return false;
}

void Container::HandleEvent(const sf::Event &event) {
  if (HasSelection() && children_[selected_child_]->IsActive()) {
    children_[selected_child_]->HandleEvent(event);
  } else if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Up) {
      SelectPrevious();
    } else if (event.key.code == sf::Keyboard::Down) {
      SelectNext();
    } else if (event.key.code == sf::Keyboard::Return) {
      if (HasSelection()) {
        children_[selected_child_]->Activate();
      }
    }
  }
}

void Container::Draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  for (const Component::Ptr& child : children_) {
    target.draw(*child, states);
  }
}

bool Container::HasSelection() const {
  return selected_child_ >= 0;
}

void Container::Select(std::size_t index) {
  if (children_[index]->IsSelectable()) {
    if (HasSelection()) {
      children_[selected_child_]->Deselect();
    }
    children_[index]->Select();
    selected_child_ = index;
  }
}

void Container::SelectNext() {
  if (!HasSelection()) return;

  int next = selected_child_;
  do {
    next = (next + 1) % children_.size();
  } while (!children_[next]->IsSelectable());

  Select(next);
}

void Container::SelectPrevious() {
  if (!HasSelection()) return;

  int previous = selected_child_;
  do {
    previous = (previous + children_.size() - 1) % children_.size();
  } while (!children_[previous]->IsSelectable());

  Select(previous);
}

}  // namespace GUI
