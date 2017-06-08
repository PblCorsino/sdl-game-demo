#ifndef __GAMESTATEMACHINE__
#define __GAMESTATEMACHINE__

#include<vector>
#include"GameState.hpp"

class GameStateMachine {

public:

  void pushState(GameState* pState);
  void changeState(GameState* pState);
  void popState();

private:

  std::vector<GameState*> m_gameStates;
};

#endif
