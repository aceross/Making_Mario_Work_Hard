// Copyright 2015, Aaron Ceross

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <memory>

#include "component.hpp"

namespace GUI {
class Container : public Component {
 public:
  typedef std::shared_ptr<Container> Ptr;

 public:
  Container();
  void Pack(Component::Ptr component);
  virtual bool IsSelectable() const;
  virtual void HandleEvent(const sf::Event& event);

 private:
  using Component::Select;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  bool HasSelection() const;
  void Select(std::size_t index);
  void SelectNext();
  void SelectPrevious();
 private:
  std::vector<Component::Ptr> children_;
  int selected_child_;
};
}  // namespace GUI

#endif  // CONTAINER_HPP
