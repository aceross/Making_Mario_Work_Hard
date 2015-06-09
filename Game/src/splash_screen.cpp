// Copyright 2015, Aaron Ceross
#include "../include/splash_screen.hpp"

SplashScreen::SplashScreen()  {}
SplashScreen::~SplashScreen() {}

void SplashScreen::LoadContent() {
  if (!font.loadFromFile("asset/font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  text.setString("Splash Screen");
  text.setFont(font);
}

void SplashScreen::UnloadContent() {}

void SplashScreen::Update() {}

void SplashScreen::Draw(sf::RenderWindow &Window) {
  Window.draw(text);
}
