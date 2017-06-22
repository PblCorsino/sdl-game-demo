#include <iostream>
#include"include/InputHandler.hpp"
#include"include/Game.hpp"

Game* Game::s_pInstance = 0;

// Initialize SDL
bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
  int flags = 0;

  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
    std::cout << "SDL init sucess" << std::endl;
    // If succedded create our window
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    // If the window creation succedded create our renderer
    if (m_pWindow != 0) {
      std::cout << "Window creation success" << std::endl;
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

      // Renderer init success
      if (m_pRenderer != 0) {
        std::cout << "Renderer creation success" << std::endl;
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
      }
      else {
        std::cout << "Renderer init fail" << std::endl;
        return false;
      }
    }
    else {
      std::cout << "Window init fail" << std::endl;
      return false;
    }
  }
  else {
    std::cout << "SDL init fail" << std::endl;
    return false; // Sdl could not initialize
  }

  std::cout << "Init success" << std::endl;
  m_bRunning = true; // Everythin inited successfully, start the main loop

  // Initialise joysticks
  TheInputHandler::Instance()->initialiseJoysticks();

  // Initialize game state machine
  m_pGameStateMachine = new GameStateMachine();
  m_pGameStateMachine->changeState(new MenuState());

  return true;
}

// Update
void Game::update() {
  m_pGameStateMachine->update();
}

// Render
void Game::render() {
  // Clear the window to black
  SDL_RenderClear(m_pRenderer);

  m_pGameStateMachine->render();

  // Show the window
  SDL_RenderPresent(m_pRenderer);
}

// Handle events
void Game::handleEvents() {
  TheInputHandler::Instance()->update();

  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
    m_pGameStateMachine->changeState(new PlayState());
  }
}

// Clean
void Game::clean() {
  std::cout << "Cleaning game" << std::endl;
  TheInputHandler::Instance()->clean();
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}

// Quit
void Game::quit() {
  m_bRunning = false;
}
