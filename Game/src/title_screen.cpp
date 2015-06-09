// Copyright 2015, Aaron Ceross
#include "../include/title_screen.hpp"

TitleScreen::TitleScreen()  {}
TitleScreen::~TitleScreen() {}

void TitleScreen::LoadContent() {
  if (!font.loadFromFile("Font1.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  text.setString("Title Screen");
  text.setFont(font);
}

void TitleScreen::UnloadContent() {}

void TitleScreen::Update() {}

void TitleScreen::Draw(sf::RenderWindow &Window) {
  Window.draw(text);
}
