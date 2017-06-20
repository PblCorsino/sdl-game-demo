#include"include/MenuState.hpp"
#include"include/Game.hpp"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->update();
  }
}

void MenuState::render() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->draw();
  } 
}

bool MenuState::onEnter() {
  std::cout << "Entering MenuState" << std::endl;  

  if (!TheTextureManager::Instance()->load("../res/button_play.png",
                                           "playbutton", TheGame::Instance()->getRenderer())) {
    return false;
  }

  if (!TheTextureManager::Instance()->load("../res/button_exit.png",
                                           "exitbutton", TheGame::Instance()->getRenderer())) {
    return false;
  }

  GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 131, 31, "playbutton"), s_menuToPlay);
  GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 131, 31, "exitbutton"), s_exitFromMenu);

  m_gameObjects.push_back(button1);
  m_gameObjects.push_back(button2);

  return true;
}

bool MenuState::onExit() {
  std::cout << "Exiting MenuState" << std::endl;

  for (auto* gameObject : m_gameObjects) {
    gameObject->clean();
  }
  m_gameObjects.clear();
  TheTextureManager::Instance()->clearFromTextureMap("playbutton");
  TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

  return true;
}

void MenuState::s_menuToPlay() {
  TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu() {
  TheGame::Instance()->quit();
}
