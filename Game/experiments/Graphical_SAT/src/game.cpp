// Copyright 2015, Aaron Ceross

#include "../include/game.hpp"

Game::Game() {
  InitialiseWindow();
  LoadAssets();
}

void Game::Run() {
  // sf::Event event;
  while (window_.isOpen()) {
    Draw();
  }
}

void Game::Draw() {
  window_.clear(sf::Color::Black);
  window_.draw(welcome_text_);
  window_.display();
}

void Game::InitialiseWindow() {
  settings_.antialiasingLevel = 8;
  window_.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                               "Graphical SAT Solver",
                                sf::Style::Default, settings_);
  window_.setFramerateLimit(60);
}

void Game::LoadAssets() {
  if (!font_.loadFromFile("font/OpenSans-Regular.ttf")) {
    std::cout << "Could not find the requested font." << std::endl;
  }
  welcome_text_.setFont(font_);
  welcome_text_.setColor(sf::Color::White);
  welcome_text_.setString("Graphical SAT Solver");
  welcome_text_.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

Game::~Game() {}
