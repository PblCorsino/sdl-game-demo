#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include"SDLGameObject.hpp"

class AnimatedGraphic : public SDLGameObject {

public:

  AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

  virtual void draw();
  virtual void update();
  virtual void clean();

private:

  int m_animSpeed = 0;
  int m_numFrames = 2;

};

#endif
