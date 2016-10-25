//
// Block.hpp for indie_studio in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed May 11 15:14:01 2016 guillaume wilmot
// Last update Sun Jun  5 04:19:17 2016 guillaume wilmot
//

#ifndef BLOCK_HPP_
# define BLOCK_HPP_

# include <iostream>
# include "irrlicht.h"

class		Block {
public:
  Block(float x, float y, float z, irr::scene::IMesh *mesh, irr::scene::ISceneManager *smgr) {
    _x = x;
    _y = y;
    _z = z;
    _mesh = mesh;
    _smgr = smgr;
    _block = NULL;
  }
  ~Block() {}

  irr::scene::IMeshSceneNode		*getBlock() const {return _block;}
  void        destroy() {_block->remove();}

  int         create(float scale) {
    if ((_block = _smgr->addMeshSceneNode(_mesh))) {
	    _extent = _block->getTransformedBoundingBox().getExtent();
	    _block->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
	    _block->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
      _block->setScale(irr::core::vector3df(scale, scale, scale));
	    _block->setPosition(irr::core::vector3df(_x * _extent.X, _extent.Y * _y, _z * _extent.Z));
	    return 0;
    }
    return -1;
  }

  irr::core::vector3df    getExtent() const {return _extent;}

private:
  irr::core::vector3df            _extent;
  irr::scene::IMeshSceneNode		  *_block;
  irr::scene::IMesh			          *_mesh;
  irr::scene::ISceneManager		    *_smgr;
  irr::scene::ISceneNodeAnimator	*_collision;
  float					_x;
  float					_y;
  float					_z;
};

#endif /* !BLOCK_HPP_ */
