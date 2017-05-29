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
        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
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
  if (!TheTextureManager::Instance()->load("../res/animate-alpha.png", "animate", m_pRenderer)) {
    return false;
  }

  // Load the game objects
  m_go = new GameObject();
  m_player = new Player();
  m_enemy = new Enemy();

  m_go->load(100, 100, 128, 82, "animate");
  m_player->load(100, 100, 128, 82, "animate");
  m_enemy->load(0, 0, 128, 82, "animate");

  // Add the game objects to the vector
  m_gameObjects.push_back(m_go);
  m_gameObjects.push_back(m_player);
  m_gameObjects.push_back(m_enemy);

  return true;
}

// Update
void Game::update() {
  // Loop through and update our objects
  for(auto& gameObject : m_gameObjects) {
    gameObject->update();
  }
}

// Render
void Game::render() {
  // Clear the window to black
  SDL_RenderClear(m_pRenderer);

  // Loop through the objects and draw them
  for(auto& gameObject : m_gameObjects) {
    gameObject->draw(m_pRenderer);
  }

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
