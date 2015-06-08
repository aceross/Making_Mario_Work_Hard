// Copyright 2015, Aaron Ceross

#include <string>
#include <iostream>

class state_manager {
 public:
    ~state_manager();
    static state_manager &get_instance();
    void set_text(std::string text);
    void draw_text();
 protected:
 private:
    state_manager();
    state_manager(state_manager const&);
    void operator = (state_manager const&);

    std::string text;
};
