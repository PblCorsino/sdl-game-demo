#include"include/InputHandler.hpp"
#include"include/Game.hpp"

InputHandler* InputHandler::s_pInstance = 0;

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

void InputHandler::update() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      TheGame::Instance()->quit();
    }
  }
}

void InputHandler::clean() {
  if (m_bJoysticksInitialised) {
    for (auto* joy : m_joysticks) {
      SDL_JoystickClose(joy);
    }
  }
}
