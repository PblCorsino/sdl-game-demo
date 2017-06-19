#ifndef __MENUBUTTON__
#define __MENUBUTTON__

#include"SDLGameObject.hpp"
#include"InputHandler.hpp"

class MenuButton : public SDLGameObject {

public:

  MenuButton(const LoaderParams* pParams, void (*callback)());

  virtual void draw();
  virtual void update();
  virtual void clean();

private:

  // callback function pointer
  void (*m_callback)();
  
  bool m_bReleased;

  enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
  };

};

#endif
