// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>

#include "title_screen_state_hpp"
#include "resource_manager.hpp"


TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, text_()
, show_text_(true)
, text_effect_time_(sf::Time::Zero)
{
  background_sprite_.setTexture(context.textures->get(Textures::TitleScreen));

  text_.setFont(context.fonts->get(Fonts::Main));
  text_.setString("Press any key to start");
  centerOrigin(text_);
  text_.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::Draw() {
  sf::RenderWindow& window = *getContext().window;
  window.draw(background_sprite_);

  if (show_text_) {
    window.draw(text_);
  }
}

bool TitleState::update(sf::Time delta_time) {
  text_effect_time_ += dt;

  if (text_effect_time_ >= sf::seconds(0.5f)) {
    mShowText = !mShowText;
    text_effect_time_ = sf::Time::Zero;
  }

  return true;
}

bool TitleState::HandleEvent(const sf::Event& event) {
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyPressed) {
    RequestStackPop();
    RequestStackPush(States::Menu);
  }
  return true;
}
