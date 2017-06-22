#include"include/PlayState.hpp"
#include"include/PauseState.hpp"
#include"include/GameOverState.hpp"
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
  // Check for collision
  if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
    TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
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

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2) {
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = p1->getPosition().getX();
  rightA = p1->getPosition().getX() + p1->getWidth();
  topA = p1->getPosition().getY();
  bottomA = p1->getPosition().getY() + p1->getHeight();

  leftB = p2->getPosition().getX();
  rightB = p2->getPosition().getX() + p2->getWidth();
  topB = p2->getPosition().getY();
  bottomB = p2->getPosition().getY() + p2->getHeight();

  // Check for collision
  if (bottomA <= topB) {
    return false;
  }
  if (topA >= bottomB) {
    return false;
  }
  if (rightA <= leftB) {
    return false;
  }
  if ( leftA >= rightB ) {
    return false;
  }

  return true;
}
