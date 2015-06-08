// Copyright 2015, Aaron Ceross

#include <string>
#include <iostream>

class GameStateManager {
 public:
    ~GameStateManager();
    static GameStateManager &get_instance();
    void set_text(std::string text);
    void draw_text();
 protected:
 private:
    GameStateManager();
    GameStateManager(GameStateManager const&);
    void operator = (GameStateManager const&);

    std::string text;
};
