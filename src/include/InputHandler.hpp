#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include<iostream>
#include<vector>
#include"SDL.h"
#include"Vector2D.hpp"

// Mouse buttons values
enum mouse_buttons {
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};

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
  bool getButtonState(int joy, int buttonNumber) {
    return m_buttonStates[joy][buttonNumber];
  }

  // Mouse
  bool getMouseButtonState(int buttonNumber) {
    return m_mouseButtonStates[buttonNumber];
  }
  Vector2D* getMousePosition() {
    return m_mousePosition;
  }

  // Keyboard
  bool isKeyDown(SDL_Scancode key);

private:

  InputHandler();
  static InputHandler* s_pInstance;

  // Handle keyboard events
  void onKeyDown();
  void onKeyUp();

  // Handle mouse events
  void onMouseMove(SDL_Event& event);
  void onMouseButtonDown(SDL_Event& event);
  void onMouseButtonUp(SDL_Event& event);

  // Handle joysticks events
  void onJoystickAxisMove(SDL_Event& event);
  void onJoystickButtonDown(SDL_Event& event);
  void onJoystickButtonUp(SDL_Event& event);

  const int m_joystickDeadZone = 10000;
  std::vector<SDL_Joystick*> m_joysticks;
  bool m_bJoysticksInitialised;
  // Vector to store the axes values
  std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
  // Vector to store the button states
  std::vector<std::vector<bool>> m_buttonStates;
  // Vector to store the mouse buttons
  std::vector<bool> m_mouseButtonStates;
  // Position of the mouse cursor
  Vector2D* m_mousePosition;
  // Keyboard state
  const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;

#endif
