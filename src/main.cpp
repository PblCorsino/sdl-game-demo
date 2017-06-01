#include<iostream>
#include"include/Game.hpp"

// Frames per second
const int FPS = 60;
// Miliseconds per frame
const int DELAY_TIME = 1000.0f / FPS;

int main() {
  Uint32 frameStart, frameTime;

  std::cout << "Game init attempt..." << std::endl;

  if (TheGame::Instance()->init("SDL game demo", 100, 100, 640, 480, false)) {
    std::cout << "Game init success" << std::endl;
    while (TheGame::Instance()->running()) {
      frameStart = SDL_GetTicks();

      TheGame::Instance()->handleEvents();
      TheGame::Instance()->update();
      TheGame::Instance()->render();

      frameTime = SDL_GetTicks() - frameStart;

      if (frameTime < DELAY_TIME) {
        SDL_Delay((int)(DELAY_TIME - frameTime));
      }
    }
  }
  else {
    std::cout << "Game init failure: " << SDL_GetError() << std::endl;
    return -1;
  }
  std::cout << "Game closing.." << std::endl;
  TheGame::Instance()->clean();

  return 0;
}
