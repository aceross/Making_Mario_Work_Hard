// Copyright 2015, Aaron Ceross

#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <memory>
#include <set>
#include <utility>

#include "category.hpp"

struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable,
                  private sf::NonCopyable {
 public:
  typedef std::unique_ptr<SceneNode> Ptr;
  typedef std::pair<SceneNode*, SceneNode*> Pair;

 public:
  explicit SceneNode(Category::Type category = Category::None);

  void AttachChild(Ptr child);
  Ptr DetachChild(const SceneNode& node);

  void Update(sf::Time delta_time, CommandQueue& commands);

  sf::Vector2f GetWorldPosition() const;
  sf::Transform GetWorldTransform() const;

  void OnCommand(const Command& command, sf::Time delta_time);
  virtual unsigned int GetCategory() const;

  void CheckSceneCollision(SceneNode& scene_graph, std::set<Pair>& collision_pairs);
  void CheckNodeCollision(SceneNode& node, std::set<Pair>& collision_pairs);

  virtual sf::FloatRect GetBoundingRect() const;

  virtual void UpdateCurrent(sf::Time delta_time, CommandQueue& commands);

 private:
  void UpdateChildren(sf::Time delta_time, CommandQueue& commands);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
  void DrawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  std::vector<Ptr>  children_;
  SceneNode*        parent_;
  Category::Type    default_category_;
};

bool Collision(const SceneNode& lhs, const SceneNode& rhs);
float Distance(const SceneNode& lhs, const SceneNode& rhs);

#endif  // SCENE_NODE_HPP
