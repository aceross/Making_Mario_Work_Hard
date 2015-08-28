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
#include "map_node.hpp"
#include "scene_node.hpp"
#include "command.hpp"
#include "command_queue.hpp"
#include "mario.hpp"
#include "zchaff_manager.hpp"
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
  TileMap& GetTileMap();
  VariableManager GetVarManager();

  bool HasActivePlayer() const;
  bool HasReachedEnd() const;

 private:
  void LoadTextures();
  void AdaptPlayerPosition(unsigned location);
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

  // struct SpawnPoint {
  //   SpawnPoint(Mario::Type type, float x, float y)
  //   : type(type)
  //   , x(x)
  //   , y(y)
  //   {}
  //
  //   Mario::Type type;
  //   float x;
  //   float y;
  // };

 private:
  sf::RenderTarget&  target_;
  sf::RenderTexture  scene_texture_;
  sf::View           level_view_;
  sf::View           mini_map_;
  TextureHolder      textures_;
  FontHolder&        fonts_;

  // tmx::MapLoader map_loader_;
  TileMap tile_map_;
  sf::Text test_;

  SceneNode                          scene_graph_;
  std::array<SceneNode*, LayerCount> scene_layers_;
  CommandQueue                       command_queue_;

  sf::FloatRect level_bounds_;
  sf::Vector2f  mario_position_;
  float         movement_speed_;
  Mario*        player_mario_;
  ZChaffManager zchaff_manager_;

  bool level_complete_;
  bool display_solution;

  bool gadget_finished_;

  bool in_start_gadget_;
  bool in_variable_gadget_;
  bool in_warp_gadget_;
  bool finished_warps_;
  bool no_warp_gadgets_;
  bool in_check_in_;
  bool in_clause_gadget_;
  bool in_check_out_;
  bool in_finish_;

  unsigned int completed_warp_gadgets_;
  unsigned int completed_clause_literals_;
  unsigned int completed_warp_pipes_;
};

#endif  // LEVEL_HPP
