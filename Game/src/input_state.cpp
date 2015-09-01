// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../include/input_state.hpp"
#include "../include/resource_manager.hpp"
#include "../include/text_utility.hpp"
#include <iostream>

InputState::InputState(StateStack& stack, Context context)
: State(stack, context)
, options_()
, options_index_(0)
, inputting_vars_(false)
, inputting_clauses_(false)
{
  // sf::Texture& texture = context.textures_->Get(Textures::TitleScreen);
  sf::Font& font = context.fonts_->Get(Fonts::Main);

  // background_sprite_.setTexture(texture);

  // A simple menu demonstration
  sf::Text set_option;
  set_option.setFont(font);
  set_option.setString("Create a SAT instance");
  CentreOrigin(set_option);
  set_option.setPosition(context.window_->getView().getSize() / 2.f);
  options_.push_back(set_option);

  // Select number of clauses
  // sf::Text select_clauses_option;
  // select_clauses_option.setFont(font);
  // select_clauses_option.setString("Quit");
  // CentreOrigin(select_clauses_option);
  // select_clauses_option.setPosition(select_variables_option.getPosition() + sf::Vector2f(0.f, 30.f));
  // options_.push_back(select_clauses_option);

  sf::Text restart_option;
  restart_option.setFont(font);
  restart_option.setString("Start Again");
  CentreOrigin(restart_option);
  restart_option.setPosition(set_option.getPosition() +
                            sf::Vector2f(0.f, 90.f));
  options_.push_back(restart_option);

  sf::Text return_option;
  return_option.setFont(font);
  return_option.setString("Return");
  CentreOrigin(return_option);
  return_option.setPosition(set_option.getPosition() +
                            sf::Vector2f(0.f, 120.f));
  options_.push_back(return_option);

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
  if (inputting_vars_ || inputting_clauses_) { options_[0].setString(""); }
  return true;
}

bool InputState::GetInput(const sf::Event &event) {
  while (inputting_vars_) {
    if (event.type == sf::Event::TextEntered) {
      if (event.text.unicode < 128) {
        std::cout << "ASCII character typed: "  << static_cast<char>(event.text.unicode) << std::endl;
        inputting_vars_ = false;
        return true;
      }
    }
  }
  return false;
}

bool InputState::HandleEvent(const sf::Event& event) {
  if (event.type != sf::Event::KeyPressed) {
    return false;
  }

  if (event.key.code == sf::Keyboard::Return) {
    if (options_index_ == Create) {
      inputting_vars_ = true;
      GetInput(event);
    } else if (options_index_ == Restart) {
      RequestStackPop();
      RequestStackPush(States::Input);
    } else if (options_index_ == Return) {
      RequestStackPop();
      RequestStackPush(States::Menu);
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
