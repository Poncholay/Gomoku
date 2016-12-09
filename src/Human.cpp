/*
** Human.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 31 19:23:37 2016 wilmot_g
** Last update Fri Dec 09 16:32:16 2016 wilmot_g
*/

#include "Human.hh"
#include "Sounds.hpp"

Human::Human(Goban &g, Displayer &d, int nb, int x, int y) : _displayer(d), _goban(g) {
  _nb = nb;
  _x = x;
  _y = y;
}

Human::~Human() {}

int        Human::play(Referee &r) {
  irr::core::line3d<irr::f32> ray;
  irr::core::vector3df        intersection;
  irr::core::triangle3df      hitTriangle;
  Block                       *placeholder;
  bool                        outside;
  int                         ret = 0;
  int                         tmp = REPLAY;

  _displayer.mutex.lock();
  placeholder = new Block(0, 0, 0, Displayer::getSmgr()->getMesh("./assets/redgo.obj"), Displayer::getSmgr());
  _displayer.mutex.unlock();
  if (placeholder->create(0.008) == -1)
    return -1;
  do {
    _i = 0;
    _j = 0;
    do {
      outside = false;
      ray.start = _displayer.getCamera()->getPosition();
      ray.end = ray.start + (_displayer.getCamera()->getTarget() - ray.start).normalize() * 10.0f;
      if (Displayer::getSmgr()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0)) {
        placeholder->setVisible();
        irr::core::vector3df extent = placeholder->getExtent();
        float size = 0.202;
        float posX = 0.0130 * extent.X;
        float posZ = 0.1595 * extent.Z;
        for (_i = 0; _i < _x; _i++)
          if (posX - ((_i + 0.5) * size / (_x - 1)) * extent.X < intersection.X) break;
        for (_j = 0; _j < _y; _j++)
          if (posZ - ((_j + 0.5) * size / (_y - 1)) * extent.Z < intersection.Z) break;
        intersection.X = posX - (_i * size / (_x - 1)) * extent.X;
        intersection.Y = 0.691 * extent.Y;
        intersection.Z = posZ - (_j * size / (_y - 1)) * extent.Z;
        int tmp = r.checkPlay(_j, _i, _nb);
        if (ret != tmp) {
          ret = tmp;
          _displayer.mutex.lock();
          placeholder->destroy();
          delete placeholder;
          placeholder = new Block(0, 0, 0, Displayer::getSmgr()->getMesh(string(string("./assets/") + (ret != REPLAY && ret != -1 ? "green" : "red") + "go.obj").c_str()), Displayer::getSmgr());
          _displayer.mutex.unlock();
          if (placeholder->create(0.008) == -1)
            return -1;
        }
        placeholder->getBlock()->setPosition(intersection);
      } else {
        outside = true;
        placeholder->setVisible(false);
      }
    } while (!_displayer.getReceiver().checkEnd() && !_displayer.getReceiver().mouseIsPressed());
  } while (!_displayer.getReceiver().checkEnd() && ((ret = r.checkPlay(_j, _i, _nb)) == REPLAY || outside));
  if (!_displayer.getReceiver().checkEnd())
    _goban.addDraught(_j, _i, _nb, true);
  _displayer.mutex.lock();
  placeholder->destroy();
  delete placeholder;
  _displayer.mutex.unlock();
  return _goban.full() ? -1 : ret;
}

string  Human::getReflexionTime() const {
  return "";
}

string  Human::getType() const {
  return "Human";
}
