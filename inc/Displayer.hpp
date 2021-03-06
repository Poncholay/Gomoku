//
// Displayer.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Wed Apr 27 10:41:04 2016 guillaume wilmot
// Last update Tue Nov 15 15:27:54 2016 Adrien Milcent
//

#ifndef DISPLAYER_HPP_
# define DISPLAYER_HPP_

using namespace std;

# include <vector>
# include <tuple>
# include <list>
# include <chrono>
# include "IPlayer.hh"
# include "Block.hpp"
# include "irrlicht.h"
# include "Axes.hpp"
# include "EventHandler.hpp"
# include "Dimensions.hh"
# include "Mutex.hpp"

enum {
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0
};

class		Displayer {
public:
  Displayer(int = GOBAN_X, int = GOBAN_Y);
  ~Displayer();

	void 				setTurn(int);
	void 				setNbTurn(int);
	void 				setScore(const string &score);
	void 				drawScore();
	void 				drawTurn();
	void 				drawWin(int);
  void        setUpdate(int, int, int);
  bool        isAnimating();
  void        setAnimate(int, int, int);
  bool        animate();
  bool        instanciate();
  bool        isRunning() const;
  bool        error() const;
  void				setCaption(const irr::core::stringw &);
	void				setTime(float);
  int					display(int = 0);

	irr::scene::ICameraSceneNode 	*getCamera() 			const {return _camera;}
	EventHandler									&getReceiver()					{return _receiver;}

  static irr::scene::ISceneManager	*getSmgr(irr::scene::ISceneManager *smgr = NULL) {
    static irr::scene::ISceneManager	*_smgr = NULL;
    return _smgr = smgr ? smgr : _smgr;
  }
  static irr::video::IVideoDriver	  *getDriver(irr::video::IVideoDriver *driver = NULL) {
    static irr::video::IVideoDriver	*_driver = NULL;
    return _driver = driver ? driver : _driver;
  }

	Mutex													mutex;

private:

  bool                          placeDraught(int, int, int);
  bool                          removeDraught(int, int);
  bool                          instanciateScene();
  bool                          instanciateLights();
  bool                          instanciateCamera();
  void                          updateFPS();
  void                          updateAnim(bool = false);

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
  vector<vector<Block *> >      _map;
  irr::scene::ICameraSceneNode  *_camera;
  irr::scene::ISceneNode        *_skydome;
  AxesSceneNode                 *_axes;
  bool                          _error;

  //Anim
  chrono::high_resolution_clock::time_point _animateTime;

  bool                          _isAnimating;
	list<tuple<int, int, int> >   _anim;
  int                           _x;
  int                           _y;
  float                         _time;
	float													_timeBase;

	int 													_turn;
	int 													_nbTurn;
	irr::gui::IGUIFont						*_font;
	string 												_score;
};

#endif /* DISPLAYER_HPP_ */
