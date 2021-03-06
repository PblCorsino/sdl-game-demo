#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include<vector>
#include"GameState.hpp"
#include"SDLGameObject.hpp"

class GameObject;

class PlayState : public GameState {

public:

  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

  virtual std::string getStateID() const {
    return s_playID;
  }

private:

  static const std::string s_playID;
  std::vector<GameObject*> m_gameObjects;
};

#endif
