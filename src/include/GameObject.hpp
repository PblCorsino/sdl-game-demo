#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

/*
  Abstract class Game Object
*/
class GameObject {
public:

  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

};

#endif
