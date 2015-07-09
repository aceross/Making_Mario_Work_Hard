// Copyright 2015, Aaron Ceross

#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>


class SceneNode : public sf::Transformable, public sf::Drawable,
                  private sf::NonCopyable {
 public:
  typedef std::unique_ptr<SceneNode> Ptr;

 public:
  SceneNode();

  void AttachChild(Ptr child);
  Ptr DetachChild(const SceneNode& node);

  void Update(sf::Time dt);

  sf::Vector2f GetWorldPosition() const;
  sf::Transform GetWorldTransform() const;

 private:
  virtual void UpdateCurrent(sf::Time dt);
  void UpdateChildren(sf::Time dt);

  virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  std::vector<Ptr>  children_;
  SceneNode*        parent_;
};

#endif  // SCENE_NODE_HPP
