// // Copyright 2015, Aaron Ceross
//
// #include <SFML/Graphics/RenderTarget.hpp>
// #include <SFML/Graphics/RenderStates.hpp>
//
// #include <cmath>
// #include <vector>
//
// #include "../include/world_object.hpp"
// #include "../include/resource_manager.hpp"
// #include "../include/data_table.hpp"
// #include "../include/command_queue.hpp"
// #include "../include/command.hpp"
//
// using namespace std::placeholders;
//
// namespace {
//   const std::vector<WorldData> Table = InitialiseWorldData();
// }
//
// WorldObject::WorldObject(Type type, const TextureHolder& textures, const FontHolder& fonts)
// : type_(type)
// , sprite_(textures.Get(Table[type].texture), Table[type].texture_rect)
// , waiting_(false)
// , move_count_(6)
// {
//
//
// }
//
// sf::Vector2f Mario::GetLocation() {
//   return location_;
// }
//
// void WorldObject::UpdateLocation(sf::Vector2f location_update) {
//   previous_location_ = location_;
//   location_ += location_update;
//   move(location_update);
// }
//
// void WorldObject::UpdateLocation(int x, int y) {
//   location_.x += x;
//   location_.y += y;
//   move(x, y);
// }
//
// void WorldObject::HandleCollision() {
//
// }
//
// void WorldObject::DrawCurrent(sf::RenderTarget &target,
//                          sf::RenderStates states) const {
//
//   target.draw(sprite_, states);
// }
//
// void WorldObject::UpdateCurrent(sf::Time delta_time, CommandQueue& commands) {
//   // if (moving_left_ || moving_right_) {
//   UpdateAnimation();
//   // }
// }
//
// unsigned int WorldObject::GetCategory() const {
//   return Category::MarioPlayer;
// }
//
// sf::FloatRect WorldObject::GetBoundingRect() const {
//   return GetWorldTransform().transformRect(sprite_.getGlobalBounds());
// }
//
//
// // May need to update as Jump animation and Walk animation
// void WorldObject::UpdateAnimation() {
//   if (Table[type_].has_animation_) {
//     sf::IntRect texture_rect = Table[type_].texture_rect;
//   // Roll left: Texture rect offset once
//   if (GetLocation().x < previous_location_.x) {
//     if (!moving_left_) {
//       moving_left_  = true;
//       moving_right_ = false;
//       texture_rect  = sf::IntRect(192, 32 , -texture_rect.width, texture_rect.height);
//     }
//     if (moving_left_) {
//       // left_face_mario_.left -= move_count_ * left_face_mario_.width;
//       // --move_count_;
//       texture_rect  = sf::IntRect(192, 32 , -texture_rect.width, texture_rect.height);
//       texture_rect.left += move_count_ * texture_rect.width;
//       --move_count_;
//     }
//   } else if (GetLocation().x > previous_location_.x) {
//     if (!moving_right_) {
//       moving_left_ = false;
//       moving_right_ = true;
//     }
//     if (moving_right_) {
//       texture_rect.left -= move_count_ * texture_rect.width;
//       --move_count_;
//     }
//   } else if (GetLocation() == previous_location_) {
//     texture_rect = Table[type_].texture_rect;
//     moving_left_ = false;
//     moving_right_ = false;
//   }
//   if (move_count_ == 3) {
//     move_count_ = 6;
//   }
//
//   sprite_.setTextureRect(texture_rect);
//   }
// }
