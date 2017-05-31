#ifndef __SDLGAMEOBJECT__
#define __SDLGAMEOBJECT__

#include<iostream>
#include"GameObject.hpp"
#include"TextureManager.hpp"
#include"LoaderParams.hpp"

class SDLGameObject : public GameObject {
public:

  SDLGameObject(const LoaderParams* pParams);
  virtual ~SDLGameObject() {}

  virtual void draw();
  virtual void update();
  virtual void clean();

protected:

  int m_x;
  int m_y;
  int m_width;
  int m_height;
  int m_currentRow;
  int m_currentFrame;
  std::string m_textureID;
};
#endif
