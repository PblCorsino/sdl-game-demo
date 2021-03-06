#include"include/SDLGameObject.hpp"
#include"include/Game.hpp"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
  : m_position(pParams->getX(), pParams->getY())
  , m_velocity(0, 0)
  , m_acceleration(0, 0) {
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();

  m_currentRow = 1;
  m_currentFrame = 1;
}

void SDLGameObject::draw() {
  if (m_velocity.getX() >= 0) {
    TheTextureManager::Instance()->drawFrame(m_textureID
                                             , (int)m_position.getX()
                                             , (int)m_position.getY()
                                             , m_width
                                             , m_height
                                             , m_currentRow
                                             , m_currentFrame
                                             , TheGame::Instance()->getRenderer());
  }
  else {
    TheTextureManager::Instance()->drawFrame(m_textureID
                                             , (int)m_position.getX()
                                             , (int)m_position.getY()
                                             , m_width
                                             , m_height
                                             , m_currentRow
                                             , m_currentFrame
                                             , TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
  }
}

void SDLGameObject::update() {
  m_velocity += m_acceleration;
  m_position += m_velocity;
}

void SDLGameObject::clean() {

}
