// Copyright 2015, Aaron Ceross

#include <string>
#include <iostream>

class GameStateManager {
 public:
    ~GameStateManager();
    static GameStateManager &GetInstance();
    void SetText(std::string text);
    void DrawText();
 protected:
 private:
    GameStateManager();
    GameStateManager(GameStateManager const&);
    void operator = (GameStateManager const&);

    std::string text;
};
