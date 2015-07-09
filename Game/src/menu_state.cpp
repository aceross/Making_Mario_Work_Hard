// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../include/menu_state.hpp"
#include "../include/resource_manager.hpp"
#include "../include/text_centring.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, options_()
, options_index_(0)
{
  sf::Texture& texture = context.textures_->Get(Textures::TitleScreen);
  sf::Font& font = context.fonts_->Get(Fonts::Main);

  background_sprite_.setTexture(texture);

  // A simple menu demonstration
  sf::Text play_option;
  play_option.setFont(font);
  play_option.setString("Play");
  CentreOrigin(play_option);
  play_option.setPosition(context.window_->getView().getSize() / 2.f);
  options_.push_back(play_option);

  sf::Text exit_option;
  exit_option.setFont(font);
  exit_option.setString("Exit");
  CentreOrigin(exit_option);
  exit_option.setPosition(play_option.getPosition() + sf::Vector2f(0.f, 30.f));
  options_.push_back(exit_option);

  UpdateOptionText();
}

void MenuState::Draw() {
  sf::RenderWindow& window = *GetContext().window_;

  window.setView(window.getDefaultView());
  window.draw(background_sprite_);

  for (const sf::Text& text : options_) {
    window.draw(text);
  }
}

bool MenuState::Update(sf::Time) {
  return true;
}

bool MenuState::HandleEvent(const sf::Event& event) {
  if (event.type != sf::Event::KeyPressed) {
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

void MenuState::UpdateOptionText() {
  if (options_.empty())
    return;

  // White all texts
  for (sf::Text& text : options_)
    text.setColor(sf::Color::White);

  // Red the selected text
  options_[options_index_].setColor(sf::Color::Red);
}
