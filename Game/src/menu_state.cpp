// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../include/menu_state.hpp"
#include "../include/resource_manager.hpp"
#include "../include/text_utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, options_()
, options_index_(0)
{
  sf::Texture& texture = context.textures_->Get(Textures::TitleScreen);
  background_sprite_.setTexture(texture);
  sf::Font& font = context.fonts_->Get(Fonts::Title);


  // A simple menu demonstration
  sf::Text select_instance_option;
  select_instance_option.setFont(font);
  select_instance_option.setString("Select Instance");
  CentreOrigin(select_instance_option);
  select_instance_option.setPosition(context.window_->getView().getSize().x / 1.86f, 400);
  select_instance_option.setCharacterSize(25);
  options_.push_back(select_instance_option);

  sf::Text input_option;
  input_option.setFont(font);
  input_option.setString("Input Instance");
  CentreOrigin(input_option);
  input_option.setPosition(select_instance_option.getPosition() +
                           sf::Vector2f(0.f, 30.f));
  input_option.setCharacterSize(25);
  options_.push_back(input_option);

  sf::Text exit_option;
  exit_option.setFont(font);
  exit_option.setString("Quit");
  CentreOrigin(exit_option);
  exit_option.setPosition(select_instance_option.getPosition() +
                          sf::Vector2f(-10.f, 60.f));
  exit_option.setCharacterSize(25);
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
    if (options_index_ == SelectInstance) {
      RequestStackPop();
      RequestStackPush(States::Select);
      // RequestStackPush(States::Game);
    } else if (options_index_ == InputInstance) {
      RequestStackPop();
      RequestStackPush(States::Input);
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

  // Yellow the selected text
  options_[options_index_].setColor(sf::Color::Yellow);
}
