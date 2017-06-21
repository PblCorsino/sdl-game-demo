#include"include/PlayState.hpp"
#include"include/PauseState.hpp"
#include"include/Game.hpp"
#include"include/Player.hpp"
#include"include/Enemy.hpp"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
  // Pause the game with ESC key
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    TheGame::Instance()->getStateMachine()->pushState(new PauseState());
  }
  for (auto* gameObject : m_gameObjects) {
    gameObject->update();
  }
}

void PlayState::render() {
  for (auto* gameObject : m_gameObjects) {
    gameObject->draw();
  }
}

bool PlayState::onEnter() {
  std::cout << "Entering PlayState" << std::endl;

  if (!TheTextureManager::Instance()->load("../res/animate-alpha.png", "helicopter", TheGame::Instance()->getRenderer())) {
    return false;
  }
  if (!TheTextureManager::Instance()->load("../res/helicopter.png", "helicopter2", TheGame::Instance()->getRenderer())) {
    return false;
  }

  GameObject* player = new Player(new LoaderParams(500, 100, 128, 82, "helicopter"));
  GameObject* enemy = new Enemy(new LoaderParams(100, 100, 180, 94, "helicopter2"));

  m_gameObjects.push_back(player);
  m_gameObjects.push_back(enemy);

  return true;
}

bool PlayState::onExit() {
  std::cout << "Exiting PlayState" << std::endl;

  for (auto* gameObject : m_gameObjects) {
    gameObject->clean();
  }
  m_gameObjects.clear();
  TheTextureManager::Instance()->clearFromTextureMap("helicopter");

  return true;
}
