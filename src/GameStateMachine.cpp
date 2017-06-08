#include"include/GameStateMachine.hpp"

// Add a state
void GameStateMachine::pushState(GameState *pState) {
  m_gameStates.push_back(pState);
  m_gameStates.back()->onEnter();
}

// Remove current state
void GameStateMachine::popState() {
  if (!m_gameStates.empty()) {
    if (m_gameStates.back()->onExit()) {
      delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }
}

// Change current state
void GameStateMachine::changeState(GameState *pState) {
  if (!m_gameStates.empty()) {
    if (m_gameStates.back()->getStateID() == pState->getStateID()) {
      return;
    }
    if (m_gameStates.back()->onExit()) {
      delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }

  // Push back our new state
  m_gameStates.push_back(pState);

  // Initialise it
  m_gameStates.back()->onEnter();
}
