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

#include <iostream>
using namespace std;

Displayer::Displayer() {
  EventHandler::get(&_receiver);
  _device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 32, false, true, true, &_receiver);
  getDriver(_driver = _device->getVideoDriver());
  getSmgr(_smgr = _device->getSceneManager());
  _guienv = _device->getGUIEnvironment();
  _then = _device->getTimer()->getTime();
  _lastFPS = -1;
  _axes = new AxesSceneNode(0, _smgr, 1);
  _caption = L"Gomoku";
  if (!(_skydome = _smgr->addSkyBoxSceneNode(
    _driver->getTexture("assets/skybox/criminal-element_up.png"),
    _driver->getTexture("assets/skybox/criminal-element_dn.png"),
    _driver->getTexture("assets/skybox/criminal-element_rt.png"),
    _driver->getTexture("assets/skybox/criminal-element_lf.png"),
    _driver->getTexture("assets/skybox/criminal-element_ft.png"),
    _driver->getTexture("assets/skybox/criminal-element_bk.png"))))
      throw std::exception();
}

Displayer::~Displayer() {}

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

int                   Displayer::manageEvents() {
  static bool			    start = false;
  const irr::f32		  MOVEMENT_SPEED = 5.f;
  const irr::u32		  now = _device->getTimer()->getTime();
  const irr::f32		  frameDeltaTime = (irr::f32)(now - _then) / 1000.f;

  if (_receiver.checkEnd())
    return 1;
  if (start) {

  }
  _then = now;
  start = true;
  return 0;
}

bool                  Displayer::update() const {
  return true;
}

bool                  Displayer::instanciate() {
  return instanciateScene() && instanciateCamera() && instanciateLights();
}

bool                  Displayer::instanciateScene() {
  Block room(0, 0, 0, _smgr->getMesh("./assets/room.obj"), _smgr);
  if (room.create(0.04) == -1) return false;
  room.getBlock()->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
  room.getBlock()->setMaterialFlag(irr::video::EMF_TEXTURE_WRAP, true);

  // srand(time(NULL));
  // float size = 0.202;
  // for (int i = 0; i < 19; i++)
  //   for (int j = 0; j < 19; j++) {
  //     if (rand() % 3) continue;
  //     Block pion(0.0130 - i * size / 18, 0.690, 0.1595 - j * size / 18, _smgr->getMesh(string(string("./assets/") + (rand() % 2 ? "white" : "black") + "go.obj").c_str()), _smgr);
  //     if (pion.create(0.008) == -1) return false;
  //   }
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

int				            Displayer::display() {
  _driver->beginScene(true, true, irr::video::SColor(255, 100, 150, 255));
  _smgr->drawAll();
  _guienv->drawAll();
  _driver->endScene();
  updateFPS();
  return manageEvents();
}

bool                  Displayer::isRunning() const {return _device->run();}
