#include"include/GameOverState.hpp"
#include"include/Game.hpp"
#include"include/AnimatedGraphic.hpp"
#include"include/MenuButton.hpp"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->update();
  }
}

void GameOverState::render() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->draw();
  }
}

void GameOverState::s_gameOverToMain() {
  TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay() {
  TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

bool GameOverState::onEnter() {
  std::cout << "Entering Game Over state" << std::endl;

  if (!TheTextureManager::Instance()->load("../res/game_over.png", "gameovertext", TheGame::Instance()->getRenderer())) {
    return false;
  }
  if (!TheTextureManager::Instance()->load("../res/button_main_menu.png", "mainbutton", TheGame::Instance()->getRenderer())) {
    return false;
  }
  if (!TheTextureManager::Instance()->load("../res/button_restart.png", "restartbutton", TheGame::Instance()->getRenderer())) {
    return false;
  }

  GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 180, 26, "gameovertext"), 2);
  GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 131, 31, "mainbutton"), s_gameOverToMain);
  GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 131, 31, "restartbutton"), s_restartPlay);

  m_gameObjects.push_back(gameOverText);
  m_gameObjects.push_back(button1);
  m_gameObjects.push_back(button2);

  return true;
  
}

bool GameOverState::onExit() {
  std::cout << "Exiting GameOverState" << std::endl;

  for (auto* gameObject : m_gameObjects) {
    gameObject->clean();
  }
  m_gameObjects.clear();
  TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
  TheTextureManager::Instance()->clearFromTextureMap("button1");
  TheTextureManager::Instance()->clearFromTextureMap("button2");

  return true;
}
