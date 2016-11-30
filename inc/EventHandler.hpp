//
// EventHandler.hpp for  in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Tue Apr 26 17:31:35 2016 guillaume wilmot
// Last update Sun Jun  5 15:43:07 2016 guillaume wilmot
//

#ifndef EVENTHANDLER_HPP_
# define EVENTHANDLER_HPP_

# include <vector>
# include "irrlicht.h"
# include "Block.hpp"

class EventHandler : public irr::IEventReceiver {
public:
  ~EventHandler() {}
  EventHandler() {
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
	     _keyIsDown[i] = false;
	     _keyWasPressed[i] = false;
    }
    _mouse = false;
    _pressed = false;
  }

  static EventHandler	*get(EventHandler *e = NULL, bool r = false) {
    static EventHandler	*_e = NULL;
    return _e = e ? e : r ? NULL : _e;
  }

  bool checkEnd() {return _keyWasPressed[irr::KEY_ESCAPE];}
  int  eventPlayer(irr::scene::ICameraSceneNode *, Block *);

  irr::core::position2di getMousePos() {_mouse = false; return _cursor;}
  bool mouseMoved() const {return _mouse;}
  bool mouseIsPressed() const {return _pressed;}
  bool isKeyDown(irr::EKEY_CODE keyCode) const {return _keyIsDown[keyCode];}
  bool wasKeyPressed(irr::EKEY_CODE keyCode) {bool tmp = _keyWasPressed[keyCode]; _keyWasPressed[keyCode] = false; return tmp;}
  bool OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
      if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED) {
	      _cursor = irr::core::position2di(event.MouseInput.X, event.MouseInput.Y);
        _mouse = true;
      }
      else if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
        _pressed = true;
      else if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
        _pressed = false;
    }
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
      _keyWasPressed[event.KeyInput.Key] = true;
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
      _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    return false;
  }

private:
  bool				                              _keyWasPressed[irr::KEY_KEY_CODES_COUNT];
  bool				                              _keyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool				                              _mouse;
  bool                                      _pressed;
  irr::core::position2di				            _cursor;
};

#endif /* EVENTHANDLER_HPP_ */
