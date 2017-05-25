#include <iostream>
#include "include/Game.hpp"

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
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
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

  // Load a image
  SDL_Surface* pTempSurface = SDL_LoadBMP("../res/rider.bmp");
  m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);

  // Obtain size of the image
  SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
  m_destinationRectangle.x = m_sourceRectangle.x = 0;
  m_destinationRectangle.y = m_sourceRectangle.y = 0;
  m_destinationRectangle.w = m_sourceRectangle.w;
  m_destinationRectangle.h = m_sourceRectangle.h;

  return true;
}

// Render
void Game::render() {
  // Clear the window to black
  SDL_RenderClear(m_pRenderer);

  // Show the image
  SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

  // Show the window
  SDL_RenderPresent(m_pRenderer);
}

// Handle events
void Game::handleEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      m_bRunning = false;
      break;

    default:
      break;
    }
  }
}

// Clean
void Game::clean() {
  std::cout << "Cleaning game" << std::endl;
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}
