#ifndef __PLAYER__
#define __PLAYER__

#include"SDLGameObject.hpp"

class Player : public SDLGameObject {
public:

  Player(const LoaderParams* pParams);
  
  virtual void draw();
  virtual void update();
  virtual void clean();
};

#endif
