#ifndef __ENEMY__
#define __ENEMY__

#include"SDLGameObject.hpp"

class Enemy : public SDLGameObject {
public:

  Enemy(const LoaderParams* pParams);

  virtual void draw();
  virtual void update();
  virtual void clean();
};

#endif
