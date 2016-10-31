/*
** EventHandler.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 31 11:31:51 2016 wilmot_g
** Last update Mon Oct 31 12:33:04 2016 wilmot_g
*/

#include "EventHandler.hpp"
#include "Displayer.hpp"

int                           EventHandler::eventPlayer(irr::scene::ICameraSceneNode *camera, Block *placeholder) {
  irr::core::line3d<irr::f32> ray;
  irr::core::vector3df        intersection;
  irr::core::triangle3df      hitTriangle;

  ray.start = camera->getPosition();
  ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 10.0f;
  if (Displayer::getSmgr()->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0)) {
    float size = 0.202;
    irr::core::vector3df extent = placeholder->getExtent();
    intersection.Y = 0.690 * extent.Y;

    cout << fmod(intersection.X + 1, size / _x) << endl;
    cout << fmod(intersection.Y + 1, size / _y) << endl;
    cout << size / _x << endl;
    cout << size / _y << endl;
    cout << (fmod(intersection.X + 1, size / _x) - (size / _x / 2) > 0) << endl;
    cout << (fmod(intersection.Y + 1, size / _y) - (size / _y / 2) > 0) << endl;
    cout << endl;
    // float posX = 0.0130 * size / _x;
    // float posZ = 0.1595 * size / _y;

    // cout << "X : " << intersection.X << endl;
    // cout << "Z : " << intersection.Z << endl << endl;
    // intersection.X = ;
    // intersection.Z = ;
    placeholder->getBlock()->setPosition(intersection);
  }
  return 0;
}
