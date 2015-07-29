// Copyright 2015, Aaron Ceross

#include <SFML/Graphics/RenderWindow.hpp>

#include "../include/title_screen_state.hpp"
#include "../include/resource_manager.hpp"
#include "../include/text_utility.hpp"


TitleScreenState::TitleScreenState(StateStack& stack, Context context)
: State(stack, context)
, text_()
, show_text_(true)
, text_effect_time_(sf::Time::Zero)
{
  background_sprite_.setTexture(context.textures_->Get(Textures::TitleScreen));

  text_.setFont(context.fonts_->Get(Fonts::Main));
  text_.setString("Press any key to start");
  CentreOrigin(text_);
  text_.setPosition(context.window_->getView().getSize() / 2.f);
}

void TitleScreenState::Draw() {
  sf::RenderWindow& window = *GetContext().window_;
  window.draw(background_sprite_);

  if (show_text_) {
    window.draw(text_);
  }
}

bool TitleScreenState::Update(sf::Time delta_time) {
  text_effect_time_ += delta_time;

  if (text_effect_time_ >= sf::seconds(0.5f)) {
    show_text_ = !show_text_;
    text_effect_time_ = sf::Time::Zero;
  }

  return true;
}

bool TitleScreenState::HandleEvent(const sf::Event& event) {
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyPressed) {
    RequestStackPop();
    RequestStackPush(States::Menu);
  }
  return true;
}
