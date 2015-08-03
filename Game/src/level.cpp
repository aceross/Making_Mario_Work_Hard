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
, level_bounds_(0.f, 0.f, level_view_.getSize().x, 2000.f)
, start_position_(level_view_.getSize().x / 2.f, level_bounds_.height -
                                                 level_view_.getSize().y / 2.f)
, scroll_speed_(-50.f)
, player_sprite_(nullptr)
{
  scene_texture_.create(target_.getSize().x, target_.getSize().y);

  LoadTextures();
  BuildScene();

  // test text
  test_.setFont(fonts.Get(Fonts::Main));
  test_.setString("In the level");

  // Prepare the view
  level_view_.setCenter(start_position_);
}

void Level::Update(sf::Time delta_time) {
  // Scroll the world, reset player velocity
  // level_view_.move(0.f, scroll_speed_ * delta_time.asSeconds());
  // player_sprite_->SetVelocity(0.f, 0.f);

  // Forward commands to scene graph, adapt velocity
  // (scrolling, diagonal correction)
  // while (!command_queue_.IsEmpty())
  //   scene_graph_.OnCommand(command_queue_.Pop(), delta_time);
  // AdaptPlayerVelocity();

  // Collision detection and response (may destroy entities)
  // HandleCollisions();

  // Regular update step, adapt position (correct if outside view)
  // scene_graph_.Update(delta_time, command_queue_);
  // AdaptPlayerPosition();
}

void Level::draw() {
  // target_.setView(level_view_);
  // target_.draw(test_);
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
  // Initialize the different layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::Ptr layer(new SceneNode());
    scene_layers_[i] = layer.get();

    scene_graph_.AttachChild(std::move(layer));
  }

  // Prepare the tiled background
  // sf::Texture& texture = textures_.Get(Textures::Desert);
  // sf::IntRect textureRect(level_bounds_);
  // textures_.setRepeated(true);

  // Add the background sprite to the scene
  // std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
  // backgroundSprite->setPosition(level_bounds_.left, level_bounds_.top);
  // scene_layers_[Background]->AttachChild(std::move(backgroundSprite));

  // Add player sprite
  std::unique_ptr<Player> player(new Player(Player::SmallPlayer, textures_,
                                 fonts_));
  player_sprite_ = player.get();
  player_sprite_->setPosition(250, 250);
  scene_layers_[Foreground]->AttachChild(std::move(player));
}

void Level::AdaptPlayerPosition() {
  // Keep player's position inside the screen bounds,
  // at least border_distance units from the border
  sf::FloatRect view_bounds(level_view_.getCenter() - level_view_.getSize() /
                                                    2.f, level_view_.getSize());
  const float border_distance = 40.f;

  sf::Vector2f position = player_sprite_->getPosition();
  position.x = std::max(position.x, view_bounds.left + border_distance);
  position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
  position.y = std::max(position.y, view_bounds.top + border_distance);
  position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
  player_sprite_->setPosition(position);
}

void Level::AdaptPlayerVelocity() {
  // sf::Vector2f velocity = mPlayerAircraft->GetVelocity();
  //
  // // If moving diagonally, reduce velocity (to have always same velocity)
  // if (velocity.x != 0.f && velocity.y != 0.f)
  //   mPlayerAircraft->SetVelocity(velocity / std::sqrt(2.f));
  //
  // // Add scrolling velocity
  // mPlayerAircraft->Accelerate(0.f, mScrollSpeed);
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
