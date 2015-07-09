// Copyright 2015, Aaron Ceross

#include <algorithm>
#include <cassert>

#include "../include/scene_node.hpp"


SceneNode::SceneNode()
: children_(), parent_(nullptr)
{}

void SceneNode::AttachChild(Ptr child) {
  child->parent_ = this;
  children_.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node) {
  auto found = std::find_if(children_.begin(), children_.end(),
                            [&] (Ptr& p) { return p.get() == &node; });

  assert(found != children_.end());

  Ptr result = std::move(*found);
  result->parent_ = nullptr;
  children_.erase(found);
  return result;
}

void SceneNode::Update(sf::Time dt) {
  UpdateCurrent(dt);
  UpdateChildren(dt);
}

void SceneNode::UpdateCurrent(sf::Time) {
  // Do nothing by default
}

void SceneNode::UpdateChildren(sf::Time dt) {
  for (Ptr& child : children_) {
    child->Update(dt);
  }
}

void SceneNode::Draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Apply transform of current node
  states.transform *= getTransform();

  // Draw node and children with changed transform
  DrawCurrent(target, states);
  DrawChildren(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget&, sf::RenderStates) const {
  // Do nothing by default
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const Ptr& child : children_) {
    child->Draw(target, states);
  }
}

sf::Vector2f SceneNode::GetWorldPosition() const {
  return GetWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::GetWorldTransform() const {
  sf::Transform transform = sf::Transform::Identity;

  for (const SceneNode* node = this; node != nullptr; node = node->parent_) {
    transform = node->getTransform() * transform;
  }

  return transform;
}
