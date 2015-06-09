// Copyright 2015, Aaron Ceross

#include <string>
#include <iostream>
#include "game_state.hpp"
#include "splash_screen.hpp"
#include "title_screen.hpp"

// Set the values for the game window
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

class GameStateManager {
 public:
    ~GameStateManager();
    static GameStateManager &GetInstance();

    void Initialise();
    void LoadContent();
    void UnloadContent();
    void Update();
    void Draw(sf::RenderWindow &Window);

    void AddState(GameState *state);

 protected:
 private:
    // GameState *current_state, *new_state;
    GameStateManager();
    GameStateManager(GameStateManager const&);
    void operator = (GameStateManager const&);
};
