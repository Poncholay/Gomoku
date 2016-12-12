//
// Displayer.cpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 10:47:57 2016 guillaume wilmot
// Last update Sun Dec  4 11:15:04 2016 Adrien Milcent
//

#include <stdexcept>
#include <unistd.h>
#include "Displayer.hpp"
#include "Sounds.hpp"

Displayer::Displayer(int x, int y) : _receiver() {
  _x = x;
  _y = y;
  _timeBase = 0.5;
  _time = _timeBase;
  _isAnimating = false;
  _error = false;
  _lastFPS = -1;
  _turn = -1;
  _nbTurn = 1;
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
    _font = _guienv->getFont("./assets/bigfont.png");
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

void                  Displayer::drawScore() {
  if (_font && _receiver.isKeyDown(irr::KEY_TAB)) {
    irr::core::stringw s(_score.c_str());
    _font->draw(s, irr::core::rect<irr::s32>(0, 0, 200, 50), irr::video::SColor(255, 255, 255, 255));
  }
}

void                  Displayer::drawTurn() {
  if (_font && _turn != -1) {
    string str = "Player " + to_string(_turn + 1) + "'s' Turn (" + to_string(_nbTurn) + ")" + (!_turn ? "(White)" : "(Black)") + "\n";
    irr::core::stringw s(str.c_str());
    _font->draw(s, irr::core::rect<irr::s32>(0, 1080 - 150, 600, 1080), irr::video::SColor(255, 255, 255, 255), true, true);
  }
}

void                  Displayer::drawWin(int p) {
  if (_font) {
    string str = p == 42 ? "Waiting for AI..." : ("Player " + to_string(p) + " wins");
    irr::core::stringw s(str.c_str());
    _font->draw(s, irr::core::rect<irr::s32>(1920 / 2 - 100, 1080 / 2 - 25, 1920 / 2 + 100, 1080 / 2 + 25), irr::video::SColor(255, 255, 255, 255), true, true);
  }
}

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
  Sounds::get().playSound("play");
  float posX = 0.0130 - y * size / (_x - 1);
  float posY = 1;
  float posZ = 0.1595 - x * size / (_y - 1);
  _map[y][x] = new Block(posX, posY, posZ, _smgr->getMesh(string(string("./assets/") + (p == 1 ? "white" : "black") + "go.obj").c_str()), _smgr);
  if (_map[y][x]->create(0.008) == -1) return false;
  _isAnimating = true;
  _animateTime = chrono::high_resolution_clock::now();
  _then = _device->getTimer()->getTime();
  _time = _timeBase;
  return true;
}

bool                  Displayer::removeDraught(int x, int y) {
  if (x >= _x || y >= _y || x < 0 || y < 0)
    return false;
  Sounds::get().playSound("pop");
  if (_map[y][x]) {
    _map[y][x]->destroy();
    delete _map[y][x];
  }
  _map[y][x] = NULL;
  _isAnimating = true;
  _animateTime = chrono::high_resolution_clock::now();
  _then = _device->getTimer()->getTime();
  _time = 0;
  return true;
}

void                  Displayer::updateAnim(bool force) {
  const irr::f32		  MOVEMENT_SPEED = 0.31f;
  const irr::u32		  now = _device->getTimer()->getTime();
  const irr::f32		  frameDeltaTime = (irr::f32)(now - _then) / 1000.f;

  if (!_anim.size() || !get<2>(_anim.front()) || get<1>(_anim.front()) < 0 || get<0>(_anim.front()) < 0 ||
      !_map[get<1>(_anim.front())][get<0>(_anim.front())])
    return;
  irr::core::vector3df pos = _map[get<1>(_anim.front())][get<0>(_anim.front())]->getBlock()->getPosition();
  irr::core::vector3df extent = _map[get<1>(_anim.front())][get<0>(_anim.front())]->getExtent();
  pos.Y -= frameDeltaTime * MOVEMENT_SPEED;
  pos.Y = pos.Y < 0.690 * extent.Y ? 0.690 * extent.Y : pos.Y;
  if (force) pos.Y = 0.690 * extent.Y;
    _map[get<1>(_anim.front())][get<0>(_anim.front())]->getBlock()->setPosition(pos);
  _then = now;
}

bool                  Displayer::isAnimating() {
  if (!_isAnimating) return animate();
  if (chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count() <
      chrono::duration_cast<chrono::microseconds>(_animateTime.time_since_epoch()).count() + static_cast<long>(_time * 1000000))
    return true;
  updateAnim(true);
  _anim.pop_front();
  _isAnimating = false;
  return animate();
}

void                  Displayer::setAnimate(int x, int y, int p) {
  tuple<int, int, int>  anim;

  get<0>(anim) = x;
  get<1>(anim) = y;
  get<2>(anim) = p;
  _anim.push_back(anim);
}

bool                  Displayer::animate() {
  if (_anim.size() == 0)
    return false;
  if (get<2>(_anim.front()) == -1) {
    _isAnimating = true;
    _animateTime = chrono::high_resolution_clock::now();
    return true;
  }
  return get<2>(_anim.front()) != 0 ? placeDraught(get<0>(_anim.front()), get<1>(_anim.front()), get<2>(_anim.front())) : removeDraught(get<0>(_anim.front()), get<1>(_anim.front()));
}

bool                  Displayer::instanciate() {
  return instanciateScene() && instanciateCamera() && instanciateLights();
}

bool                  Displayer::instanciateScene() {
  _smgr->getMesh("./assets/redgo.obj");
  _smgr->getMesh("./assets/greengo.obj");
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
  _camera->setPosition(irr::core::vector3df(0.2, 0.7, -0.2));
  _camera->setTarget(irr::core::vector3df(0, 0.5, 0));
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

int				            Displayer::display(int win) {
  _driver->beginScene(true, true, irr::video::SColor(255, 100, 150, 255));
  if (isAnimating())
    updateAnim();
  mutex.lock();
  _smgr->drawAll();
  _guienv->drawAll();
  mutex.unlock();
  drawScore();
  win ? drawWin(win) : drawTurn();
  _driver->endScene();
  updateFPS();
  return _receiver.checkEnd();
}

void                  Displayer::setTurn(int t) {_turn = t;}
void                  Displayer::setNbTurn(int t) {_nbTurn = t;}
void                  Displayer::setScore(const string &score) {_score = score;}
void                  Displayer::setTime(float newTime) {_time = newTime;}
bool                  Displayer::isRunning() const {return _device->run();}
bool                  Displayer::error() const {return _error;}
