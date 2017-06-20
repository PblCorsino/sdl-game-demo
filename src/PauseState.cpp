#include"include/PauseState.hpp"
#include"include/Game.hpp"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
  TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay() {
  TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->update();
  }
}

void PauseState::render() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->draw();
  }
}

bool PauseState::onEnter() {

  std::cout << "Entering PauseState" << std::endl;

  if (!TheTextureManager::Instance()->load("../res/button_resume.png", "resumebutton", TheGame::Instance()->getRenderer())) {
    return false;
  }

  if (!TheTextureManager::Instance()->load("../res/button_main_menu.png", "mainbutton", TheGame::Instance()->getRenderer())) {
    return false;
  }

  GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 131, 31, "mainbutton"), s_pauseToMain);
  GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 131, 31, "resumebutton"), s_resumePlay);

  m_gameObjects.push_back(button1);
  m_gameObjects.push_back(button2);

  return true;
}

bool PauseState::onExit() {

  std::cout << "Exiting PauseState" << std::endl;

  for (auto* gameObject : m_gameObjects) {
    gameObject->clean();
  }
  m_gameObjects.clear();
  TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
  TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

  // Reset the mouse button states to false
  TheInputHandler::Instance()->reset();

  return true;
}
