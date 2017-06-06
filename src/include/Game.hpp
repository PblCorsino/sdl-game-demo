#ifndef __Game__
#define __Game__

#include<vector>
#include<SDL.h>
#include"Player.hpp"
#include"Enemy.hpp"

class Game {
public:

  // Create the public instance function
  static Game* Instance() {
    if (s_pInstance == 0) {
      s_pInstance = new Game();
      return s_pInstance;
    }
    return s_pInstance;
  }
  ~Game() {}

  bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
  void render();
  void update();
  void handleEvents();
  void clean();
  void quit();

  SDL_Renderer* getRenderer() const {
    return m_pRenderer;
  }

  // A function to access the private running variable
  bool running() {
    return m_bRunning;
  }

private:

  // Constructor is private to make a singleton class
  Game() {};
  // Create the s_pInstance member variable
  static Game* s_pInstance;

  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;

  Player* m_player;
  Enemy* m_enemy;
  std::vector<GameObject*> m_gameObjects;

  int m_currentFrame;

  bool m_bRunning;
};

// Create the typedef
typedef Game TheGame;

#endif

