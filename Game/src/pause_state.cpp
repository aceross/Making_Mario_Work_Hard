// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../include/pause_state.hpp"
#include "../include/resource_manager.hpp"
#include "../include/text_utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, background_sprite_()
, paused_text_()
, instruction_text_()
{
  sf::Font&    font = context.fonts_->Get(Fonts::Main);
  sf::Vector2f window_size(context.window_->getSize());

  paused_text_.setFont(font);
  paused_text_.setString("Paused");
  paused_text_.setCharacterSize(70);
  CentreOrigin(paused_text_);

  paused_text_.setPosition(0.5f * window_size.x, 0.4f * window_size.y);

  instruction_text_.setFont(font);
  instruction_text_.setString("Press 'R' to resume or 'M' for menu.");
  instruction_text_.setCharacterSize(20);
  CentreOrigin(instruction_text_);

  instruction_text_.setPosition(0.5f * window_size.x, (0.4f * window_size.y) - 50.f);
}

void PauseState::Draw() {
  sf::RenderWindow& window = *GetContext().window_;
  window.setView(window.getDefaultView());

  sf::RectangleShape background_shape;
  background_shape.setFillColor(sf::Color(0, 0, 0, 150));
  background_shape.setSize(window.getView().getSize());

  window.draw(background_shape);
  window.draw(paused_text_);
  window.draw(instruction_text_);
}

bool PauseState::Update(sf::Time) {
  return false;
}

bool PauseState::HandleEvent(const sf::Event& event) {
  if (event.type != sf::Event::KeyPressed) {
    return false;
  }

  if (event.key.code == sf::Keyboard::R) {
    RequestStackPop();
  } else if (event.key.code == sf::Keyboard::M) {
    RequestStackPop();
    RequestStackPop();
    RequestStackPush(States::Select);
  }
  return true;

}

void PauseState::UpdateOptionText() {
  if (options_.empty())
    return;

  // White all texts
  for (sf::Text& text : options_)
    text.setColor(sf::Color::White);

  // Yellow the selected text
  options_[options_index_].setColor(sf::Color::Yellow);
}
