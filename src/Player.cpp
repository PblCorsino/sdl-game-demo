#include "include/Player.hpp"
#include "include/InputHandler.hpp"

Player::Player(const LoaderParams* pParams)
  : SDLGameObject(pParams) {
}

void Player::draw() {
  SDLGameObject::draw();
}

void Player::update() {
  m_velocity.setX(0);
  m_velocity.setY(0);

  // handle user inputs
  handleInput();

  m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

  SDLGameObject::update();
}

void Player::clean() {

}

void Player::handleInput() {
  Vector2D* target = TheInputHandler::Instance()->getMousePosition();

  m_velocity = *target - m_position;

  m_velocity /= 50;
}
