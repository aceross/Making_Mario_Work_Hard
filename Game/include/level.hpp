// Copyright 2015, Aaron Ceross

#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>

#include "resource_manager.hpp"
#include "resource_identifiers.hpp"
#include "sprite_node.hpp"
#include "scene_node.hpp"
#include "command.hpp"
#include "command_queue.hpp"

// #include <Book/Aircraft.hpp>

// Forward declaration
namespace sf {
  class RenderWindow;
}

class Level : private sf::NonCopyable {
 public:
  explicit Level(sf::RenderWindow& window);
  void     Update(sf::Time delta_time);
  void     Draw();

  CommandQueue& GetCommandQueue();

 private:
  void LoadTextures();
  void BuildScene();
  void AdaptPlayerPosition();
  void AdaptPlayerVelocity();

 private:
  enum Layer { Background, Air, LayerCount };


 private:
  sf::RenderWindow& window_;
  sf::View          level_view_;
  TextureHolder     textures_;

  SceneNode                          scene_graph_;
  std::array<SceneNode*, LayerCount> scene_layers_;
  CommandQueue                       command_queue_;

  sf ::FloatRect level_bounds_;
  sf ::Vector2f  start_position_;
  float          scroll_speed_;
  // Aircraft* mPlayerAircraft;
};

#endif  // LEVEL_HPP
