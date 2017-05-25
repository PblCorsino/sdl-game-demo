#ifndef __Game__
#define __Game__

#include<SDL.h>

class Game {
public:
  Game() {}
  ~Game() {}

  // Simply set the running variable to true
  bool init(const char* title, int xpos, int ypos, int width, int height, int flags); 
  void render(); 
  void update() {}
  void handleEvents(); 
  void clean(); 

  // A function to access the private running variable
  bool running() {
    return m_bRunning;
  }

private:
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;

  bool m_bRunning;
};

#endif
