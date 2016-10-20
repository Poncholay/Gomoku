//
// Displayer.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 10:47:57 2016 guillaume wilmot
// Last update Sun Jun  5 22:42:26 2016 guillaume wilmot
//

#include <stdexcept>
#include "Displayer.hpp"

#include "Block.hpp"

Displayer::Displayer() {
  EventHandler::get(&_receiver);
  _device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 32, false, false, true, &_receiver);
  getDriver(_driver = _device->getVideoDriver());
  getSmgr(_smgr = _device->getSceneManager());
  _guienv = _device->getGUIEnvironment();
  _then = _device->getTimer()->getTime();
  _lastFPS = -1;
  _axes = new AxesSceneNode(0, _smgr, 1);
  _caption = L"Gomoku";
  if (!(_skydome = _smgr->addSkyDomeSceneNode(_driver->getTexture("assets/skydome.jpg"), 16, 8, 0.95f, 2.0f)))
    throw std::exception();
}

Displayer::~Displayer() {}

void				Displayer::setCaption(const irr::core::stringw &caption) {_caption = caption;}

void				Displayer::updateFPS() {
  int				fps = _driver->getFPS();

  if (_lastFPS != fps) {
      irr::core::stringw	tmp(_caption);

      tmp += " fps: ";
      tmp += fps;
      tmp += " | triangle: ";
      tmp += _driver->getPrimitiveCountDrawn();
      _device->setWindowCaption(tmp.c_str());
      _lastFPS = fps;
    }
}

int                 Displayer::manageEvents() {
  static bool			  start = false;
  const irr::f32		MOVEMENT_SPEED = 5.f;
  const irr::u32		now = _device->getTimer()->getTime();
  const irr::f32		frameDeltaTime = (irr::f32)(now - _then) / 1000.f;

  if (_receiver.checkEnd())
    return (1);
  if (start) {

  }
  _then = now;
  start = true;
  return (0);
}

bool                 Displayer::instanciate() {
  return instanciateScene() && instanciateCamera() && instanciateLights();
}

bool                 Displayer::instanciateScene() {
  Block table(0, 0, 0, _smgr->getMesh("./assets/table/armchair_and_table3.obj"), _smgr);
  Block room(0, 0, 0, _smgr->getMesh("./assets/room/house_interior.obj"), _smgr);
  bool ret = table.create(3) == -1 || room.create(0.04) == -1 ? false : true;
  if (ret) {
    irr::core::vector3df pos = table.getBlock()->getPosition();
    pos.X -= 5;
    pos.Z += 2;
    table.getBlock()->setPosition(pos);
  }
  return ret;
}

bool                 Displayer::instanciateCamera() {
  irr::SKeyMap       keyMap[4];
  keyMap[0].Action = irr::EKA_MOVE_FORWARD;
  keyMap[0].KeyCode = irr::KEY_KEY_Z;
  keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
  keyMap[1].KeyCode = irr::KEY_KEY_S;
  keyMap[2].Action = irr::EKA_STRAFE_LEFT;
  keyMap[2].KeyCode = irr::KEY_KEY_Q;
  keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
  keyMap[3].KeyCode = irr::KEY_KEY_D;

  return (_camera = Displayer::getSmgr()->addCameraSceneNodeFPS(0, 50, 0.005f, -1, keyMap, 4)) != NULL;
}

bool                 Displayer::instanciateLights() {
  _smgr->setAmbientLight(irr::video::SColorf(0.5, 0.5, 0.5, 0));
  return (!_smgr->addLightSceneNode(0, irr::core::vector3df(0, 20, 0), irr::video::SColorf(1.0f, 1.0, 1.0f, 1.0f), 30.0f) ||
      !_smgr->addLightSceneNode(0, irr::core::vector3df(50, 10, 0), irr::video::SColorf(1.0f, 1.0, 1.0f, 1.0f), 30.0f) ||
      !_smgr->addLightSceneNode(0, irr::core::vector3df(0, 10, 50), irr::video::SColorf(1.0f, 1.0, 1.0f, 1.0f), 30.0f) ||
      !_smgr->addLightSceneNode(0, irr::core::vector3df(50, 10, -50), irr::video::SColorf(1.0f, 1.0, 1.0f, 1.0f), 30.0f) ||
      !_smgr->addLightSceneNode(0, irr::core::vector3df(-50, 10, 50), irr::video::SColorf(1.0f, 1.0, 1.0f, 1.0f), 30.0f)) ? false : true;
}

int				Displayer::display() {
  if (!instanciate()) return -1;

  /**/
  _camera->setPosition(irr::core::vector3df(0, 10, 0));
  /**/

  while (_device->run()) {
      _driver->beginScene(true, true, irr::video::SColor(255, 100, 150, 255));
      // _axes->render();
      _smgr->drawAll();
      _guienv->drawAll();
      _driver->endScene();
      updateFPS();
      if (int ret = manageEvents() != 0) return ret;
    }
  if (_device->run())
    return (0);
  return (-1);
}
