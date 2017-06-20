#include"include/InputHandler.hpp"
#include"include/Game.hpp"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() {
  // Initialise mouse buttons
  reset();
  // Initialise the mouse position
  m_mousePosition = new Vector2D(0, 0);
}

// Reset the mouse button states to false
void InputHandler::reset() {
  for (int i = 0; i < 3; i++) {
    m_mouseButtonStates.push_back(false);
  }
}

void InputHandler::initialiseJoysticks() {

  // Init the Joystick subsystem if not already started
  if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  }

  // Check for the number of Joysticks and store then in a vector
  if (SDL_NumJoysticks() > 0) {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
      SDL_Joystick* joy = SDL_JoystickOpen(i);
      if (joy) {
        m_joysticks.push_back(joy);
        // Add a pair of vectors for the axis
        m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
        // Initialise buttons
        std::vector<bool> tempButtons;

        for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
          tempButtons.push_back(false);
        }

        m_buttonStates.push_back(tempButtons);
      }
      else {
        std::cout << SDL_GetError();
      }
    }

    // Start listening the joystick events
    SDL_JoystickEventState(SDL_ENABLE);
    m_bJoysticksInitialised = true;

    std::cout << "Initialised " << m_joysticks.size() << "joystick(s)" << std::endl;
  }
  else {
    std::cout << "No Joysticks found" << std::endl;
    m_bJoysticksInitialised= false;
  }
}

int InputHandler::xvalue(int joy, int stick) {
  if (m_joystickValues.size() > 0) {
    if (stick == 1) {
      return m_joystickValues[joy].first->getX();
    }
    else if (stick == 2) {
      return m_joystickValues[joy].second->getX();
    }
  }
  return 0;
}

int InputHandler::yvalue(int joy, int stick) {
  if (m_joystickValues.size() > 0) {
    if (stick == 1) {
      return m_joystickValues[joy].first->getY();
    }
    else if (stick == 2) {
      return m_joystickValues[joy].second->getY();
    }
  }
  return 0;
}

void InputHandler::update() {
  SDL_Event event;

  // Update keyboard events array
  m_keystates = SDL_GetKeyboardState(0);

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      TheGame::Instance()->quit();
      break;

    case SDL_JOYAXISMOTION:
      onJoystickAxisMove(event);
      break;
    case SDL_JOYBUTTONDOWN:
      onJoystickButtonDown(event);
      break;
    case SDL_JOYBUTTONUP:
      onJoystickButtonUp(event);
      break;

    case SDL_MOUSEMOTION:
      onMouseMove(event);
      break;
    case SDL_MOUSEBUTTONDOWN:
      onMouseButtonDown(event);
      break;
    case SDL_MOUSEBUTTONUP:
      onMouseButtonUp(event);
      break;

    case SDL_KEYDOWN:
      onKeyDown();
      break;
    case SDL_KEYUP:
      onKeyUp();
      break;
    default:
      break;
    }
  }
}

// Handler for key press events
void InputHandler::onKeyDown() {
  // Update keyboard events array
  m_keystates = SDL_GetKeyboardState(0);
}

// Handler for key release events
void InputHandler::onKeyUp() {
  // Update keyboard events array
  m_keystates = SDL_GetKeyboardState(0);
}

// Handler for mouse click events
void InputHandler::onMouseButtonDown(SDL_Event& event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_mouseButtonStates[LEFT] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
      m_mouseButtonStates[MIDDLE] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_mouseButtonStates[RIGHT] = true;
    }
  }
}

// Handler for mouse release events
void InputHandler::onMouseButtonUp(SDL_Event &event) {
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_mouseButtonStates[LEFT] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
      m_mouseButtonStates[MIDDLE] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_mouseButtonStates[RIGHT] = false;
    }
  }
}

// Handler for mouse move event
void InputHandler::onMouseMove(SDL_Event& event) {
  if (event.type == SDL_MOUSEMOTION) {
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
  }
}

// Handler for joysticks axis movements
void InputHandler::onJoystickAxisMove(SDL_Event& event) {
  if (event.type == SDL_JOYAXISMOTION) {
    int whichOne = event.jaxis.which; // get which controller

    // left stick move left or right
    if (event.jaxis.axis == 0) {
      if (event.jaxis.value > m_joystickDeadZone) {
        m_joystickValues[whichOne].first->setX(1);
      }
      else if (event.jaxis.value < -m_joystickDeadZone) {
        m_joystickValues[whichOne].first->setX(-1);
      }
      else {
        m_joystickValues[whichOne].first->setX(0);
      }
    }

    // Left stick move up or down
    if (event.jaxis.axis == 1) {
      if (event.jaxis.value > m_joystickDeadZone) {
        m_joystickValues[whichOne].first->setY(1);
      }
      else if (event.jaxis.value < -m_joystickDeadZone) {
        m_joystickValues[whichOne].first->setY(-1);
      }
      else {
        m_joystickValues[whichOne].first->setY(0);
      }
    }

    // Right stick move left or right
    if (event.jaxis.axis == 3) {
      if (event.jaxis.value > m_joystickDeadZone) {
        m_joystickValues[whichOne].second->setX(1);
      }
      else if (event.jaxis.value < -m_joystickDeadZone) {
        m_joystickValues[whichOne].second->setX(-1);
      }
      else {
        m_joystickValues[whichOne].second->setX(0);
      }
    }

    // Left stick move up or down
    if (event.jaxis.axis == 4) {
      if (event.jaxis.value > m_joystickDeadZone) {
        m_joystickValues[whichOne].second->setY(1);
      }
      else if (event.jaxis.value < -m_joystickDeadZone) {
        m_joystickValues[whichOne].second->setY(-1);
      }
      else {
        m_joystickValues[whichOne].second->setY(0);
      }
    }

  }
}

// Handler for joysticks button press
void InputHandler::onJoystickButtonDown(SDL_Event& event) {
  if (event.type == SDL_JOYBUTTONDOWN) {
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = true;
  }
}

// Handler for joysticks button release
void InputHandler::onJoystickButtonUp(SDL_Event& event) {
  if (event.type == SDL_JOYBUTTONUP) {
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = false;
  }
}

// Check for key down in the keystates array
// Keyboard scancodes in https://wiki.libsdl.org/SDL_Scancode
bool InputHandler::isKeyDown(SDL_Scancode key) {
  if (m_keystates != 0) {
    if (m_keystates[key] == 1) {
      return true;
    }
  }
  return false;
}

void InputHandler::clean() {
  if (m_bJoysticksInitialised) {
    for (auto* joy : m_joysticks) {
      SDL_JoystickClose(joy);
    }
  }
}
