#ifndef __MENUSTATE__
#define __MENUSTATE__

#include"GameState.hpp"

class MenuState : public GameState {

public:

  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const {
    return s_menuID;
  }

private:

  static const std::string s_menuID;
};

#endif