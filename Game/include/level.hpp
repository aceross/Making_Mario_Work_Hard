// Copyright 2015, Aaron Ceross

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <array>
#include <queue>

#include "resource_manager.hpp"
#include "resource_identifiers.hpp"
#include "sprite_node.hpp"
#include "scene_node.hpp"
#include "command.hpp"
#include "command_queue.hpp"
#include "player.hpp"
#include "tile_map.hpp"

// Forward declaration
namespace sf {
class RenderTarget;
}

class Level : private sf::NonCopyable {
 public:
  Level(sf::RenderTarget& output_target, FontHolder& fonts);
  void Update(sf::Time delta_time);
  void draw();

  CommandQueue& GetCommandQueue();

  bool HasActivePlayer() const;
  bool HasReachedEnd() const;

 private:
  void LoadTextures();
  void AdaptPlayerPosition();
  // void AdaptPlayerVelocity();
  void HandleCollisions();

  void BuildScene();

  void AddEnemies();
  void AddSingleEnemy();
  void SpawnEnemies();

  void DestroyEntitiesOutsideView();

  sf::FloatRect GetViewBounds() const;
  sf::FloatRect GetPlayBounds() const;

 private:
  enum Layer { Background, Foreground, LayerCount };

 private:
  sf::RenderTarget&  target_;
  sf::RenderTexture  scene_texture_;
  sf::View           level_view_;
  TextureHolder      textures_;
  FontHolder&        fonts_;

  TileMap tilemap;

  sf::Text test_;

  SceneNode                          scene_graph_;
  std::array<SceneNode*, LayerCount> scene_layers_;
  CommandQueue                       command_queue_;

  sf::FloatRect level_bounds_;
  sf::Vector2f  start_position_;
  float         scroll_speed_;
  Player*       player_sprite_;
};

#endif  // LEVEL_HPP
