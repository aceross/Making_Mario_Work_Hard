// Copyright 2015, Aaron Ceross

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include "animation.hpp"
#include "tile_map.hpp"
#include "../lib/zchaff/SAT.h"


class Player : public sf::Sprite {
public:
  void StartLevel();
  bool start_gadget_;
  bool in_variable_gadget_;
  bool in_warp_gadget_;
  bool in_clause_;
  bool in_check_in_;
  bool in_check_out_;
  bool finish_;

  unsigned int num_variables_;
  unsigned int num_clauses_;

  unsigned int variable_gadget_ID_;
  unsigned int clause_gadget_ID_;

  int variable_assignment_;

  sf::Vector2f forward_move_;
  sf::Vector2f jump_move_;
  sf::Vector2f fall_move_;
private:
  void AddLeftJump();
  void AddRightJump();

  std::queue<sf::Vector2f> command_queue_;

  // Movement Queues
  void CreateStartGadgetQueue();
  int SelectVariable();

 public:
  explicit Player(sf::Time frameTime = sf::seconds(0.2f),
                  bool paused = false, bool looped = true);
  Player(sf::Texture);

  void update();

  void SolveLevel(SAT_Manager sm);

  // methods for animation
  void UpdateAnimation(sf::Time deltaTime);
  void setAnimation(const Animation& animation);
  void setFrameTime(sf::Time time);
  void play();
  void play(const Animation& animation);
  void pause();
  void stop();
  void setLooped(bool looped);
  void setColor(const sf::Color& color);
  const Animation* getAnimation() const;
  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;
  sf::FloatRect getSize() const;
  sf::FloatRect GetBoundingRect() const;
  bool isLooped() const;
  bool isPlaying() const;
  sf::Time getFrameTime() const;
  void setFrame(std::size_t newFrame, bool resetTime = true);

  void UpdatePosition(sf::Vector2f movement);

  Animation player_move_left;
  Animation player_move_right;

  void handleInput();

  sf::Texture texture;
  // AnimationHandler animation_handler_;

  // movement boolean values
  bool moving_right_  = false;
  bool moving_left_   = false;
  bool jumping_       = false;
  bool falling_       = true;
  bool top_collision_ = false;
  bool can_move_      = false;

  // rect values
  float bottom, left, right, top;

  sf::Vector2f position_;

  std::vector<sf::Vector2f> collision_points_;

 private:
  const Animation* animation_;
  sf::Time frame_time_;
  sf::Time current_time_;
  std::size_t current_frame_;
  bool is_paused_;
  bool is_looped_;
  const sf::Texture* texture_;
  sf::Vertex vertices_[4];

  bool HasCollision(Player* p, Tile t);

  float speed_          = 32.0f;
  float fall_speed_     = 5.2f;
  bool noKeyWasPressed_ = true;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // PLAYER_HPP
