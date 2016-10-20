//
// Displayer.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 10:41:04 2016 guillaume wilmot
// Last update Sun Jun  5 21:46:38 2016 guillaume wilmot
//

#ifndef DISPLAYER_HPP_
# define DISPLAYER_HPP_

# include "irrlicht.h"
# include "Axes.hpp"
# include "EventHandler.hpp"

class		Displayer {
public:
  Displayer();
  ~Displayer();

  void				setCaption(const irr::core::stringw &caption);
  int					display();

  static irr::scene::ISceneManager	*getSmgr(irr::scene::ISceneManager *smgr = NULL) {
    static irr::scene::ISceneManager	*_smgr = NULL;
    return _smgr = smgr ? smgr : _smgr;
  }
  static irr::video::IVideoDriver	  *getDriver(irr::video::IVideoDriver *driver = NULL) {
    static irr::video::IVideoDriver	*_driver = NULL;
    return _driver = driver ? driver : _driver;
  }

private:

  bool                          instanciate();
  bool                          instanciateScene();
  bool                          instanciateLights();
  bool                          instanciateCamera();
  void                          updateFPS();
  int                           manageEvents();

  //Irrlicht
  EventHandler                  _receiver;
  irr::IrrlichtDevice           *_device;
  irr::video::IVideoDriver      *_driver;
  irr::scene::ISceneManager	    *_smgr;
  irr::gui::IGUIEnvironment	    *_guienv;

  //Window
  irr::core::stringw		        _caption;
  irr::u32			                _then;
  int                           _lastFPS;

  //Miscelanneous
  irr::scene::ICameraSceneNode  *_camera;
  irr::scene::ISceneNode        *_skydome;
  AxesSceneNode                 *_axes;
};

#endif /* DISPLAYER_HPP_ */
