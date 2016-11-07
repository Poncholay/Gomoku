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

Displayer::Displayer(int x, int y) : _receiver() {
  _x = x;
  _y = y;
  _time = 0.5;
  _isAnimating = false;
  _error = false;
  _lastFPS = -1;
  EventHandler::get(&_receiver);
  irr::SIrrlichtCreationParameters params = irr::SIrrlichtCreationParameters();
  params.AntiAlias = 32;
  params.DriverType = irr::video::EDT_OPENGL;
  params.WindowSize = irr::core::dimension2d<irr::u32>(1920, 1080);
  params.EventReceiver = &_receiver;
  params.Fullscreen = false;
  params.Vsync = true;
  if ((_device = irr::createDeviceEx(params))) {
    getDriver(_driver = _device->getVideoDriver());
    getSmgr(_smgr = _device->getSceneManager());
    _device->getCursorControl()->setVisible(false);
    _guienv = _device->getGUIEnvironment();
    _then = _device->getTimer()->getTime();
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

bool                  Displayer::placeDraught(int x, int y, int p) {
  float               size = 0.202;

  if (x >= _x || y >= _y || x < 0 || y < 0)
    return false;
  if (_map[y][x])
    removeDraught(x, y);
  float posX = 0.0130 - y * size / (_x - 1);
  float posY = 1;
  float posZ = 0.1595 - x * size / (_y - 1);
  _map[y][x] = new Block(posX, posY, posZ, _smgr->getMesh(string(string("./assets/") + (p == 1 ? "white" : "black") + "go.obj").c_str()), _smgr);
  if (_map[y][x]->create(0.008) == -1) return false;
  _isAnimating = true;
  _animateTime = chrono::high_resolution_clock::now();
  _then = _device->getTimer()->getTime();
  return true;
}

bool                  Displayer::removeDraught(int x, int y) {
  if (x >= _x || y >= _y || x < 0 || y < 0)
    return false;
  _map[y][x]->destroy();
  delete _map[y][x];
  return true;
}

void                  Displayer::updateAnim(bool force) {
  const irr::f32		  MOVEMENT_SPEED = 0.31f;
  const irr::u32		  now = _device->getTimer()->getTime();
  const irr::f32		  frameDeltaTime = (irr::f32)(now - _then) / 1000.f;

  irr::core::vector3df pos = _map[get<1>(_anim[0])][get<0>(_anim[0])]->getBlock()->getPosition();
  irr::core::vector3df extent = _map[get<1>(_anim[0])][get<0>(_anim[0])]->getExtent();
  pos.Y -= frameDeltaTime * MOVEMENT_SPEED;
  pos.Y = pos.Y < 0.690 * extent.Y ? 0.690 * extent.Y : pos.Y;
  if (force) pos.Y = 0.690 * extent.Y;
  _map[get<1>(_anim[0])][get<0>(_anim[0])]->getBlock()->setPosition(pos);
  _then = now;
}

bool                  Displayer::isAnimating() {
  if (!_isAnimating) return false;
  if (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count() <
      chrono::duration_cast<chrono::microseconds>(_animateTime.time_since_epoch()).count() + static_cast<long>(_time * 1000000))
    return true;
  updateAnim(true);
  _isAnimating = false;
  animate();
  return false;
}

void                  Displayer::setAnimate(int x, int y, int p) {
tuple<int, int, int>  anim;


get<0>(anim) = x;
get<1>(anim) = y;
get<2>(anim) = p;

_anim.push_back(anim);
  // _animX = x;
  // _animY = y;
  // _p = p;
}

bool                  Displayer::animate() {
  if (_anim.size()) {
    // _p != 0 ? placeDraught(_animX, _animY, _p) : removeDraught(_animX, _animY);
    get<2>(_anim[0]) != 0 ? placeDraught(get<0>(_anim[0]), get<1>(_anim[0]), get<2>(_anim[0])) : removeDraught(get<0>(_anim[0]), get<1>(_anim[0]));
    return true;
  }
  return false;
}

bool                  Displayer::instanciate() {
  return instanciateScene() && instanciateCamera() && instanciateLights();
}

bool                  Displayer::instanciateScene() {
  Block room(0, 0, 0, _smgr->getMesh("./assets/room.obj"), _smgr);
  Block goban(0, 0, 0, _smgr->getMesh("./assets/goban.obj"), _smgr, IDFlag_IsPickable);
  if (room.create(0.04) == -1 || goban.create(0.04) == -1) return false;
  goban.getBlock()->setTriangleSelector(_smgr->createTriangleSelector(goban.getBlock()));
  room.getBlock()->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
  room.getBlock()->setMaterialFlag(irr::video::EMF_TEXTURE_WRAP, true);
  goban.getBlock()->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
  goban.getBlock()->setMaterialFlag(irr::video::EMF_TEXTURE_WRAP, true);
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
  billboard->setMaterialTexture(0, _driver->getTexture("./assets/particle.bmp"));
  billboard->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  billboard->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
  return _smgr->addLightSceneNode(billboard, irr::core::vector3df(0, 0, 0), irr::video::SColorf(1, 1, 1), 1) != NULL;
}

int				            Displayer::display(bool anim) {
  _driver->beginScene(true, true, irr::video::SColor(255, 100, 150, 255));
  if (isAnimating())
    updateAnim();
  mutex.lock();
  _smgr->drawAll();
  _guienv->drawAll();
  mutex.unlock();
  _driver->endScene();
  updateFPS();
  return _receiver.checkEnd();
}

bool                  Displayer::isRunning() const {return _device->run();}
bool                  Displayer::error() const {return _error;}
