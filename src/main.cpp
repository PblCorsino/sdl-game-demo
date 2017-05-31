#include<iostream>
#include"include/Game.hpp"

int main() {
  std::cout << "Game init attempt..." << std::endl;

  if (TheGame::Instance()->init("SDL game demo", 100, 100, 640, 480, false)) {
    std::cout << "Game init success" << std::endl;
    while (TheGame::Instance()->running()) {
      TheGame::Instance()->handleEvents();
      TheGame::Instance()->update();
      TheGame::Instance()->render();

      SDL_Delay(10);
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
