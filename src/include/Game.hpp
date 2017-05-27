#ifndef __Game__
#define __Game__

#include<SDL.h>
#include"TextureManager.hpp"
#include"Player.hpp"

class Game {
public:
  Game() {}
  ~Game() {}

  bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); 
  void render(); 
  void update(); 
  void handleEvents(); 
  void clean(); 

  // A function to access the private running variable
  bool running() {
    return m_bRunning;
  }

private:
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;

  GameObject m_go;
  Player m_player;

  int m_currentFrame;

  bool m_bRunning;
};

#endif
