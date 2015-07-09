// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>

#include "../include/level.hpp"

Level::Level(sf::RenderWindow& window)
: window_(window)
, level_view_(window.getDefaultView())
, textures_()
, scene_graph_()
, scene_layers_()
, level_bounds_(0.f, 0.f, level_view_.getSize().x, 2000.f)
, start_position_(level_view_.getSize().x / 2.f, level_bounds_.height -
                                                 level_view_.getSize().y / 2.f)
, scroll_speed_(-50.f)
// , mPlayerAircraft(nullptr)
{
  LoadTextures();
  BuildScene();

  // Prepare the view
  level_view_.setCenter(start_position_);
}

void Level::Update(sf::Time delta_time) {
  // Scroll the world, reset player velocity
  level_view_.move(0.f, scroll_speed_ * delta_time.asSeconds());
  // mPlayerAircraft->setVelocity(0.f, 0.f);

  // Forward commands to scene graph, adapt velocity
  // (scrolling, diagonal correction)
  while (!command_queue_.IsEmpty())
    scene_graph_.OnCommand(command_queue_.Pop(), delta_time);
  AdaptPlayerVelocity();

  // Regular update step, adapt position (correct if outside view)
  scene_graph_.Update(delta_time);
  AdaptPlayerPosition();
}

void Level::Draw() {
  window_.setView(level_view_);
  window_.draw(scene_graph_);
}

CommandQueue& Level::GetCommandQueue() {
  return command_queue_;
}

void Level::LoadTextures() {
  // textures_.load(Textures::Eagle, "Media/Textures/Eagle.png");
  // textures_.load(Textures::Raptor, "Media/Textures/Raptor.png");
  // textures_.load(Textures::Desert, "Media/Textures/Desert.png");
}

void Level::BuildScene() {
  // Initialize the different layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::Ptr layer(new SceneNode());
    scene_layers_[i] = layer.get();

    scene_graph_.AttachChild(std::move(layer));
  }

  // Prepare the tiled background
  sf::Texture& texture = textures_.get(Textures::Desert);
  sf::IntRect textureRect(level_bounds_);
  texture.setRepeated(true);

  // Add the background sprite to the scene
  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
  backgroundSprite->setPosition(level_bounds_.left, level_bounds_.top);
  scene_layers_[Background]->attachChild(std::move(backgroundSprite));

  // Add player's aircraft
  // std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
  // mPlayerAircraft = leader.get();
  // mPlayerAircraft->setPosition(mSpawnPosition);
  // scene_layers_[Air]->attachChild(std::move(leader));
}

void Level::AdaptPlayerPosition() {
  // Keep player's position inside the screen bounds,
  // at least borderDistance units from the border
  // sf::FloatRect viewBounds(level_view_.getCenter() - level_view_.getSize() /
  //                                                   2.f, level_view_.getSize());
  // const float borderDistance = 40.f;
  //
  // sf::Vector2f position = mPlayerAircraft->getPosition();
  // position.x = std::max(position.x, viewBounds.left + borderDistance);
  // position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
  // position.y = std::max(position.y, viewBounds.top + borderDistance);
  // position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
  // mPlayerAircraft->setPosition(position);
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
