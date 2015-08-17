// Copyright 2015, Aaron Ceross

#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <string>

#include "game_state.hpp"
#include "player.hpp"
#include "tile_map.hpp"
#include "collision.hpp"
#include "zchaff_manager.hpp"
#include "tmx/MapLoader.h"
#include "tmx/tmx2box2d.h"

class LevelState : public GameState {
 private:
  sf::View view;
  sf::View mini_map_;
  sf::Text level_text;
  sf::Font font;
  sf::Sprite  tiles;
  sf::FloatRect block;

  Player player;
  TileMap tilemap;

  tmx::MapLoader ml;
  ZChaffManager zchaff_manager_;

  const Animation* current_animation_;

  // float speed_          = 32.0f;
  // float jump_speed_     = 4.0f;
  // float fall_speed_     = 5.2f;
  bool noKeyWasPressed_ = true;

  sf::Vector2f movement_;

  bool HasCollision(Player p, Tile t);
  void ManageCollision();
  void InitialiseWorld();

 public:
  virtual void draw(const sf::RenderWindow &window);
  virtual void update();
  virtual void handleInput();

  explicit LevelState(GameStateManager* gsm);

  //create a box2D world
  b2World world;

  virtual ~LevelState();
};

#endif  // LEVEL_STATE_HPP
