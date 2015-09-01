// Copyright 2015, Aaron Ceross

#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "state_identifiers.hpp"
#include "resource_identifiers.hpp"
#include "mapfile_handler.hpp"

namespace sf {
class RenderWindow;
}

class StateStack;
class PlayerManager;

class State {
 public:
  typedef std::unique_ptr<State> Ptr;

  struct Context {
    Context(sf::RenderWindow& window, TextureHolder& textures_,
            FontHolder& fonts_, PlayerManager& player_manager,
            MapfileHandler& mapfile_hander);

    sf::RenderWindow*  window_;
    TextureHolder*     textures_;
    FontHolder*        fonts_;
    PlayerManager*     player_manager_;
    MapfileHandler*    mapfile_handler_;
  };

 public:
  State(StateStack& stack, Context context);
  virtual      ~State();
  virtual void Draw()                              = 0;
  virtual bool Update(sf::Time dt)                 = 0;
  virtual bool HandleEvent(const sf::Event& event) = 0;

 protected:
  void RequestStackPush(States::ID stateID);
  void RequestStackPop();
  void RequestStateClear();
  void SetMapfile(std::string mapfile);

  Context GetContext() const;

 private:
  StateStack*    states_;
  Context        context_;
};

#endif  // STATE_HPP
