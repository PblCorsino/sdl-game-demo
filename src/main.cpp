#include<SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

bool g_bRunning = false; // This will create a loop

// Initialize SDL
bool init(const char* title, int xpos, int ypos, int width, int height, int flags) {
  if(SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
    // If succedded create our window
    g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    // If the window creation succedded create our renderer
    if(g_pWindow != 0) {
      g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    }
  }
  else {
    return false; // Sdl could not initialize
  }

  return true;
}

// Render
void render() {
  // Set to black
  // This function expects RGB and Alpha as color values
  SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

  // Clear the window to black
  SDL_RenderClear(g_pRenderer);

  // Show the window
  SDL_RenderPresent(g_pRenderer);
}

int main() {
  // Initialize SDL
  if(init("Chapter 1: Setting up SDL"
          , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480
          , SDL_WINDOW_SHOWN)) {
    g_bRunning = true;
  }
  else {
    return 1;
  }

  // Everythin succeded, lets draw the window
  while(g_bRunning) {
    render();
  }

  // Clean up SDL
  SDL_Quit();

  return 0;
}
