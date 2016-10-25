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

class EventHandler : public irr::IEventReceiver {
public:
  ~EventHandler() {}
  EventHandler() {
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
	     _keyIsDown[i] = false;
	     _keyWasPressed[i] = false;
    }
  }

  static EventHandler	*get(EventHandler *e = NULL, bool r = false) {
    static EventHandler	*_e = NULL;
    return _e = e ? e : r ? NULL : _e;
  }

  bool checkEnd() {return _keyWasPressed[irr::KEY_ESCAPE];}

  irr::core::position2di getMouse() {_mouse = false; return (_cursor);}
  bool wasMouse() const {return (_mouse);}
  bool IsKeyDown(irr::EKEY_CODE keyCode) const {return (_keyIsDown[keyCode]);}
  bool WasKeyPressed(irr::EKEY_CODE keyCode) {bool tmp = _keyWasPressed[keyCode]; _keyWasPressed[keyCode] = false; return (tmp);}
  bool OnEvent(const irr::SEvent &event) {
    cout << "ReceiveEvent" << endl;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
	    _cursor = irr::core::position2di(event.MouseInput.X, event.MouseInput.Y);
	    _mouse = true;
    }
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
      _keyWasPressed[event.KeyInput.Key] = true;
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
  }

private:
  bool				                              _keyWasPressed[irr::KEY_KEY_CODES_COUNT];
  bool				                              _keyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool				                              _mouse;
  irr::core::position2di				            _cursor;
};

#endif /* EVENTHANDLER_HPP_ */
