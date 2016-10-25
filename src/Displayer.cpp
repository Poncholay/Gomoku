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
#include <unistd.h>
#include "Displayer.hpp"

float size = 0.202;

Displayer::Displayer(int x, int y) {
  _x = x;
  _y = y;
  EventHandler::get(&_receiver);
  _error = false;
  if ((_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 32, false, true, true, &_receiver))) {
    getDriver(_driver = _device->getVideoDriver());
    getSmgr(_smgr = _device->getSceneManager());
    _guienv = _device->getGUIEnvironment();
    _then = _device->getTimer()->getTime();
    _lastFPS = -1;
    vector<Block *> row = vector<Block *>       (x, NULL);
    _map = vector<vector<Block *> >             (y, row);
    _axes = new AxesSceneNode(0, _smgr, 1);
    _caption = L"Gomoku";
    _skydome = _smgr->addSkyBoxSceneNode(
      _driver->getTexture("assets/skybox/criminal-element_up.png"),
      _driver->getTexture("assets/skybox/criminal-element_dn.png"),
      _driver->getTexture("assets/skybox/criminal-element_rt.png"),
      _driver->getTexture("assets/skybox/criminal-element_lf.png"),
      _driver->getTexture("assets/skybox/criminal-element_ft.png"),
      _driver->getTexture("assets/skybox/criminal-element_bk.png"));
  } else
      _error = true;
}

Displayer::~Displayer() {_device->drop();}

void				          Displayer::setCaption(const irr::core::stringw &caption) {_caption = caption;}

void				          Displayer::updateFPS() {
  int				          fps = _driver->getFPS();

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

int                   Displayer::manageEvents(bool anim) {
  static bool			    start = false;

  if (_receiver.checkEnd())
    return 1;
  if (!anim && start) {

  }
  start = true;
  return 0;
}

bool                  Displayer::placeDraught(int x, int y, int p) {
  if (_map[y][x])
    removeDraught(x, y);
  float posX = 0.0130 - y * size / _x;
  float posY = 1;
  float posZ = 0.1595 - x * size / _y;
  _map[y][x] = new Block(posX, posY, posZ, _smgr->getMesh(string(string("./assets/") + (p == 1 ? "white" : "black") + "go.obj").c_str()), _smgr);
  if (_map[y][x]->create(0.008) == -1) return false;
  _isAnimating = true;
  _animateTime = chrono::high_resolution_clock::now();
  return true;
}

bool                  Displayer::removeDraught(int x, int y) {
  _map[y][x]->destroy();
  delete _map[y][x];
  return true;
}

void                  Displayer::updateAnim() {
  const irr::f32		  MOVEMENT_SPEED = 0.31f;
  const irr::u32		  now = _device->getTimer()->getTime();
  const irr::f32		  frameDeltaTime = (irr::f32)(now - _then) / 1000.f;

  irr::core::vector3df pos = _map[_animY][_animX]->getBlock()->getPosition();
  irr::core::vector3df extent = _map[_animY][_animX]->getExtent();
  pos.Y -= frameDeltaTime * MOVEMENT_SPEED;
  cout << "extent " << extent.Y << " - " << extent.Y * 0.690 << endl;

  pos.Y = pos.Y < 0.690 * extent.Y ? 0.690 * extent.Y : pos.Y;
  _map[_animY][_animX]->getBlock()->setPosition(pos);
  _then = now;
}

bool                  Displayer::isAnimating() {
  float time = 1;
  if (!_isAnimating) return false;
  if (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count() < chrono::duration_cast<chrono::microseconds>(_animateTime.time_since_epoch()).count() + static_cast<long>(time * 1000000))
    return true;
  _isAnimating = false;
  return false;
}

bool                  Displayer::animate(int x, int y, int p) {
  _animX = x;
  _animY = y;
  return p != 0 ? placeDraught(x, y, p) : removeDraught(x, y);
}

bool                  Displayer::instanciate() {
  return instanciateScene() && instanciateCamera() && instanciateLights();
}

bool                  Displayer::instanciateScene() {
  Block room(0, 0, 0, _smgr->getMesh("./assets/room.obj"), _smgr);
  if (room.create(0.04) == -1) return false;
  room.getBlock()->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
  room.getBlock()->setMaterialFlag(irr::video::EMF_TEXTURE_WRAP, true);
  return true;
}

bool                  Displayer::instanciateCamera() {
  irr::SKeyMap        keyMap[4];
  keyMap[0].Action = irr::EKA_MOVE_FORWARD;
  keyMap[0].KeyCode = irr::KEY_KEY_Z;
  keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
  keyMap[1].KeyCode = irr::KEY_KEY_S;
  keyMap[2].Action = irr::EKA_STRAFE_LEFT;
  keyMap[2].KeyCode = irr::KEY_KEY_Q;
  keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
  keyMap[3].KeyCode = irr::KEY_KEY_D;

  if (!(_camera = Displayer::getSmgr()->addCameraSceneNodeFPS(0, 50, 0.001f, -1, keyMap, 4))) return false;
  _camera->setNearValue(0.001f);
  _camera->setPosition(irr::core::vector3df(0, 0.5, 0));
  return true;
}

bool                  Displayer::instanciateLights() {
  _smgr->setAmbientLight(irr::video::SColorf(0.5, 0.5, 0.5, 0));
  irr::scene::IBillboardSceneNode *billboard = _smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(0.2, 0.2));
  billboard->setPosition(irr::core::vector3df(-0.5, 0.8, 0.02));
  billboard->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  billboard->setMaterialTexture(0, _driver->getTexture("assets/particle.bmp"));
  billboard->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  billboard->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
  return _smgr->addLightSceneNode(billboard, irr::core::vector3df(0, 0, 0), irr::video::SColorf(1, 1, 1), 1) != NULL;
}

int				            Displayer::display(bool anim) {
  _driver->beginScene(true, true, irr::video::SColor(255, 100, 150, 255));
  if (isAnimating()) updateAnim();
  _smgr->drawAll();
  _guienv->drawAll();
  _driver->endScene();
  updateFPS();
  return manageEvents(anim);
}

bool                  Displayer::isRunning() const {return _device->run();}
bool                  Displayer::error() const {return _error;}
