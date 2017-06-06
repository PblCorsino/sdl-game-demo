#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include<iostream>
#include<vector>
#include"SDL.h"
#include"Vector2D.hpp"

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
  int xvalue(int joy, int stick);
  int yvalue(int joy, int stick);

private:

  InputHandler() {};

  static InputHandler* s_pInstance;

  const int m_joystickDeadZone = 10000;
  std::vector<SDL_Joystick*> m_joysticks;
  bool m_bJoysticksInitialised;
  // Vector to store the axes values
  std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
};

typedef InputHandler TheInputHandler;

#endif
