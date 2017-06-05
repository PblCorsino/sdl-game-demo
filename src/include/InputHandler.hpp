#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include<iostream>
#include<vector>
#include"SDL.h"

class InputHandler {

public:
  static InputHandler* Instance() {
    if (s_pInstance == 0) {
      s_pInstance = new InputHandler();
    }

    return s_pInstance;
  }
  ~InputHandler() {}

  void update();
  void clean();

  // Joysticks
  void initialiseJoysticks();
  bool joysticksInitialised() {
    return m_bJoysticksInitialised;
  }

private:

  InputHandler() {};

  static InputHandler* s_pInstance;

  std::vector<SDL_Joystick*> m_joysticks;
  bool m_bJoysticksInitialised;
};

typedef InputHandler TheInputHandler;

#endif
