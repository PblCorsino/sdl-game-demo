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
  // Keyboard controls
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
    m_velocity.setX(2);
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
    m_velocity.setX(-2);
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
    m_velocity.setY(-2);
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
    m_velocity.setY(2);
  }
  // Mouse controls
  if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
    // Follow the mouse
    Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    m_velocity = (*vec - m_position) / 100;
  }

  // Joystick controls
  if (TheInputHandler::Instance()->joysticksInitialised()) {
    // Change velocity if the user click the button 3 (Y) in the joystick
    if (TheInputHandler::Instance()->getButtonState(0, 3)) {
      m_velocity.setX(1);
    }
    // Move the player with both Joystick axis
    if (TheInputHandler::Instance()->xvalue(0, 1) > 0 ||
        TheInputHandler::Instance()->xvalue(0, 1) < 0) {
      m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
    }
    if (TheInputHandler::Instance()->yvalue(0, 1) > 0 ||
        TheInputHandler::Instance()->yvalue(0, 1) < 0) {
      m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
    }
    if (TheInputHandler::Instance()->xvalue(0, 2) > 0 ||
        TheInputHandler::Instance()->xvalue(0, 2) < 0) {
      m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
    }
    if (TheInputHandler::Instance()->yvalue(0, 2) > 0 ||
        TheInputHandler::Instance()->yvalue(0, 2) < 0) {
      m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
    }
  }
}
