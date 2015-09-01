// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../include/input_state.hpp"
#include "../include/resource_manager.hpp"
#include "../include/text_utility.hpp"

InputState::InputState(StateStack& stack, Context context)
: State(stack, context)
, options_()
, options_index_(0)
{
  // sf::Texture& texture = context.textures_->Get(Textures::TitleScreen);
  sf::Font&    font    = context.fonts_->Get(Fonts::Main);

  // background_sprite_.setTexture(texture);

  // A simple menu demonstration
  sf::Text select_variables_option;
  select_variables_option.setFont(font);
  select_variables_option.setString("Set Variables");
  CentreOrigin(select_variables_option);
  select_variables_option.setPosition(context.window_->getView().getSize() / 2.f);
  options_.push_back(select_variables_option);

  // Select number of clauses
  sf::Text select_clauses_option;
  select_clauses_option.setFont(font);
  select_clauses_option.setString("Quit");
  CentreOrigin(select_clauses_option);
  select_clauses_option.setPosition(select_variables_option.getPosition() + sf::Vector2f(0.f, 30.f));
  options_.push_back(select_clauses_option);

  UpdateOptionText();
}

void InputState::Draw() {
  sf::RenderWindow& window = *GetContext().window_;

  window.setView(window.getDefaultView());
  window.draw(background_sprite_);

  for (const sf::Text& text : options_) {
    window.draw(text);
  }
}

bool InputState::Update(sf::Time) {
  return true;
}

bool InputState::HandleEvent(const sf::Event& event) {
  if (event.type != sf::Event::KeyPressed ||
      event.type != sf::Event::TextEntered) {
    return false;
  }

  if (event.key.code == sf::Keyboard::Return) {
    if (options_index_ == Play) {
      RequestStackPop();
      RequestStackPush(States::Game);
    } else if (options_index_ == Exit) {
      RequestStackPop();
    }
  } else if (event.key.code == sf::Keyboard::Up) {
    // Decrement and wrap-around
    if (options_index_ > 0)
      --options_index_;
    else
      options_index_ = options_.size() - 1;

    UpdateOptionText();
  } else if (event.key.code == sf::Keyboard::Down) {
    if (options_index_ < options_.size() - 1)
      ++options_index_;
    else
      options_index_ = 0;

    UpdateOptionText();
  }
  return true;
}

void InputState::UpdateOptionText() {
  if (options_.empty())
    return;

  // White all texts
  for (sf::Text& text : options_)
    text.setColor(sf::Color::White);

  // Yellow the selected text
  options_[options_index_].setColor(sf::Color::Yellow);
}
