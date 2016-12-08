/*
** Menu.hh for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/inc
**
** Made by wilmot_g
** Login   <wilmot_g@epitech.net>
**
** Started on  Mon Oct 31 13:38:26 2016 wilmot_g
** Last update Mon Nov 07 22:34:47 2016 wilmot_g
*/

#ifndef MENU_HH_
# define MENU_HH_

#define NANOVG_GL2_IMPLEMENTATION
#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif
#include <fstream>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include "demo.h"
#include "perf.h"

void drawWindow(NVGcontext*, const char *, float, float, float, float);
void drawDropDown(NVGcontext*, const char *, float, float, float, float);
void drawButton(NVGcontext*, const char*, float, float, float, float, NVGcolor);
void drawCheckBox(NVGcontext*, const char*, float, float, float, float, bool);
int  drawImg(NVGcontext *, int, int, int, int, int);
void drawSlider(NVGcontext*, float, float, float, float, float);
void drawEditBox(NVGcontext*, const char *, float, float, float, float);

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
  bool        _quit;
  int         _typeOfGameValue;
  bool        _click;
  bool        _validate;
  float       _volume;
  float       _pxRatio;
  int         _tmpX;
  int         _tmpY;
  int         _clicked;
  int         _pos;
  bool        *_choices;
  bool        _selected;
  std::vector<std::string>  _vectorOfGame;
  std::vector<std::string>  _testOfTextBox;

public:
  Menu();
  ~Menu();

  int   play();
  bool  isInit();
  void 	drawBackGround();
  void  setWindowAndVar();
  void  detectClick();
  void  checkTypeOfGame();
  void  drawAllCheckBox();
  void  drawCheckBoxWithText(std::string, int);
  void  drawEditBoxDepth();
  void  checkControlSound();
  void  checkButtons();
  void  setValues(int, float, bool *);
  bool  *getRules() const;
  float getVolume() const;
  int   getDepth() const;
};

#endif /* !MENU_HH_ */
