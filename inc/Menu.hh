/*
** Menu.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 31 13:38:26 2016 wilmot_g
** Last update Mon Oct 31 13:44:45 2016 wilmot_g
*/

#ifndef MENU_HH_
# define MENU_HH_

#define NANOVG_GL2_IMPLEMENTATION
#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif
#include <fstream>
#include <iostream>
#include <GLFW/glfw3.h>
#include "demo.h"
#include "perf.h"

class         Menu {
  GLFWwindow* _window;
  PerfGraph   _fps;
  NVGcontext* _vg;
  MenuData    _data;
  bool        _init;
  double      _previousTime;
  int         _backgroundImage;
  int         _windowWidth;
  int         _windowHeight;
  double      _timer;
  double      _duration;
  double      _mousePosX;
  double      _mousePosY;
  double      _mouseClickPosX;
  double      _mouseClickPosY;
  int         _frameBufferWidth;
  int         _frameBufferHeight;
  bool        _play;
  bool        _settings;
  bool        _quit;
  const char  *_menu;
  const char  *_typeOfGame;

public:
  Menu();
  ~Menu();

  int   play();
  int   drawImg(int, int, int, int, int);
  int   drawParagraph(float, float, float, const char *);
  bool  isInit();
};

#endif /* !MENU_HH_ */
