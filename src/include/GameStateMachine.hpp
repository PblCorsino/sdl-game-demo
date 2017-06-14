#ifndef __GAMESTATEMACHINE__
#define __GAMESTATEMACHINE__

#include<vector>
#include"MenuState.hpp"
#include"PlayState.hpp"

class GameStateMachine {

public:

  void pushState(GameState* pState);
  void changeState(GameState* pState);
  void popState();

  void update();
  void render();

private:

  std::vector<GameState*> m_gameStates;
};

#endif
