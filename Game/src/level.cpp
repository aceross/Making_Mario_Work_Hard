// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <memory>

#include "../include/level.hpp"

Level::Level(sf::RenderTarget& output_target, FontHolder& fonts)
: target_(output_target)
, scene_texture_()
, level_view_(output_target.getDefaultView())
, textures_()
, fonts_(fonts)
, scene_graph_()
, scene_layers_()
, level_bounds_(0.f, 0.f, level_view_.getSize().x, level_view_.getSize().y)
, start_position_(level_view_.getSize().x / 2.f, level_bounds_.height -
                                                 level_view_.getSize().y / 2.f)
, movement_speed_(2.5f)
, player_sprite_(nullptr)
{
  scene_texture_.create(target_.getSize().x, target_.getSize().y);

  LoadTextures();
  BuildScene();

  // Prepare the main view and the mini-map
  level_view_.setCenter(player_sprite_->getPosition());
  level_view_.zoom(0.57f);
}

void Level::Update(sf::Time delta_time) {
  if (!command_queue_.IsEmpty()) {
    scene_graph_.OnCommand(command_queue_.Pop(), delta_time);
    player_sprite_->move(0, 10);
    std::cout << "Command Executed" << std::endl;
  }

  // Collision detection and response (may destroy entities)
  // HandleCollisions();

  // Regular update step, adapt position (correct if outside view)
  scene_graph_.Update(delta_time, command_queue_);
}

void Level::draw() {
  target_.setView(level_view_);
  target_.draw(scene_graph_);
}

CommandQueue& Level::GetCommandQueue() {
  return command_queue_;
}

void Level::LoadTextures() {
  textures_.Load(Textures::Mario, "resources/gfx/mario_bros.png");
  textures_.Load(Textures::Koopa, "resources/gfx/enemies.png");
  textures_.Load(Textures::World, "resources/gfx/tile_set.png");
}

void Level::BuildScene() {
  // Initialise the different layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    Category::Type category = (i == Foreground) ?
                              Category::SceneForegroundLayer : Category::None;
    SceneNode::Ptr layer(new SceneNode(category));
    scene_layers_[i] = layer.get();
    scene_graph_.AttachChild(std::move(layer));
  }

  // Start and load SAT solver
  zchaff_manager_.LoadInstance();

  // Read in the tile map
  std::unique_ptr<MapNode> ml(new MapNode());
  assert(ml->ml_.Load("simple_collision_test.tmx"));
  ml->ml_.UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
  scene_layers_[Background]->AttachChild(std::move(ml));

  // Add player sprite
  std::unique_ptr<Player> player(new Player(Player::SmallMario, textures_,
                                 fonts_));
  player_sprite_ = player.get();
  player_sprite_->setPosition(64, 160);
  // player_sprite_->UpdateLocation(64, 160);
  scene_layers_[Background]->AttachChild(std::move(player));
}

void Level::AdaptPlayerPosition() {
  // Keep player's position inside the screen bounds,
  // at least border_distance units from the border
  // sf::FloatRect view_bounds(level_view_.getCenter() - level_view_.getSize() /
  //                                                   2.f, level_view_.getSize());
  // const float border_distance = 40.f;

  sf::Vector2f position = player_sprite_->getPosition();
  // printf("First postion x = %d y = %d\n", position.x, position.y);
  // position.x = std::max(position.x, view_bounds.left + border_distance);
  // position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
  // position.y = std::max(position.y, view_bounds.top + border_distance);
  // position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
  player_sprite_->setPosition(position);
  // sf::Vector2i location_update = static_cast<sf::Vector2i>(position);
  // printf("location_update x = %d y = %d\n", position.x, position.y);
  // player_sprite_->UpdateLocation(position);
}

void Level::HandleCollisions() {
  // std::set<SceneNode::Pair> collision_pairs;

  // scene_graph_.CheckSceneCollision(scene_graph_, collision_pairs);
  //
  // for (SceneNode::Pair pair : collision_pairs) {
  //   if (matchesCategories(pair, Category::Player, Category::EnemyAircraft))
  //   {
  //     auto& player = static_cast<Aircraft&>(*pair.first);
  //     auto& enemy = static_cast<Aircraft&>(*pair.second);
  //
  //     // Collision: Player damage = enemy's remaining HP
  //     player_sprite_.damage(enemy.getHitpoints());
  //     enemy.destroy();
  //   }
  //
  //   else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
  //   {
  //     auto& player = static_cast<Aircraft&>(*pair.first);
  //     auto& pickup = static_cast<Pickup&>(*pair.second);
  //
  //     // Apply pickup effect to player, destroy projectile
  //     pickup.apply(player);
  //     pickup.destroy();
  //     player.playLocalSound(mCommandQueue, SoundEffect::CollectPickup);
  //   }
  //
  //   else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
  //       || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
  //   {
  //     auto& aircraft = static_cast<Aircraft&>(*pair.first);
  //     auto& projectile = static_cast<Projectile&>(*pair.second);
  //
  //     // Apply projectile damage to aircraft, destroy projectile
  //     aircraft.damage(projectile.getDamage());
  //     projectile.destroy();
  //   }
  // }

}
