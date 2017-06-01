#include "include/Player.hpp"

Player::Player(const LoaderParams* pParams)
  : SDLGameObject(pParams) {
}

void Player::draw() {
  SDLGameObject::draw();
}

void Player::update() {
  m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
  m_velocity.setX(2);

  SDLGameObject::update();
}

void Player::clean() {
  
}
