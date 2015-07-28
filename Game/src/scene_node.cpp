// Copyright 2015, Aaron Ceross

#include <algorithm>
#include <cassert>
#include <cmath>
#include <set>

#include "../include/scene_node.hpp"


SceneNode::SceneNode(Category::Type category)
: children_()
, parent_(nullptr)
, default_category_(category)
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

void SceneNode::Update(sf::Time delta_time, CommandQueue& commands) {
  UpdateCurrent(delta_time, commands);
  UpdateChildren(delta_time, commands);
}

void SceneNode::UpdateCurrent(sf::Time delta_time, CommandQueue& commands) {
  // Do nothing by default
}

void SceneNode::UpdateChildren(sf::Time delta_time, CommandQueue& commands) {
  for (Ptr& child : children_) {
    child->Update(delta_time, commands);
  }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Apply transform of current node
  states.transform *= getTransform();

  // Draw node and children with changed transform
  DrawCurrent(target, states);
  DrawChildren(target, states);

  // Draw bounding rectangle
  DrawBoundingRect(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget&, sf::RenderStates) const {
  // Do nothing by default
}

void SceneNode::DrawChildren(sf::RenderTarget& target,
                             sf::RenderStates states) const {
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

void SceneNode::DrawBoundingRect(sf::RenderTarget& target,
                                 sf::RenderStates states) const {
  sf::FloatRect rect = GetBoundingRect();
  sf::RectangleShape shape;

  shape.setPosition(sf::Vector2f(rect.left, rect.top));
  shape.setSize(sf::Vector2f(rect.width, rect.height));
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(sf::Color::Green);
  shape.setOutlineThickness(1.f);

  target.draw(shape);
}

unsigned int SceneNode::GetCategory() const {
  return default_category_;
}

void SceneNode::OnCommand(const Command& command, sf::Time delta_time) {
  // Command current node, if category matches
  for (Ptr& child : children_) {
    child->OnCommand(command, delta_time);
  }
}

void SceneNode::CheckSceneCollision(Scene& scene_graph,
                                    std::set<Pair> &collision_pairs) {
  CheckNodeCollision(scene_graph, collision_pairs);

  for (Ptr& child : scene_graph.children_) {
    child->CheckNodeCollision(node, collision_pairs);
  }
}

void SceneNode::CheckNodeCollision(Scene& &node,
                                  std::set<Pair> &collision_pairs) {
  if (this != &node && Collision(*this, node)) {
    collision_pairs.insert(std::minmax(this, &node));
  }
  for (Ptr& child : children_) {
    child->CheckNodeCollision(node, collision_pairs);
  }
}

sf::FloatRect SceneNode::GetBoundingRect() const {
  return sf::FloatRect();
}

bool Collision(const SceneNode& lhs, const SceneNode& rhs) {
  return lhs.GetBoundingRect().intesects(rhs.GetBoundingRect());
}
