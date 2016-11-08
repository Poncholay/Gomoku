/*
** Menu.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src/Menu
**
** Made by cheesy shift
** Login   <saurs_f@epitech.net>
**
** Started on  Mon Nov 07 22:35:02 2016 saurs_f
** Last update Mon Nov 07 22:52:44 2016 wilmot_g
*/

#include "Menu.hh"
#include "nanovg.h"
#include "nanovg_gl.h"
#include "Sounds.hpp"

using namespace std;

#define ICON_CHECK 0x2713

int blowup = 0;
int screenshot = 0;
int premult = 0;

void printErrorFunc(int error, const char *desc)
{
	cerr << "GLFW error " << error << ": " << desc << endl;
}

static char* cpToUTF8(int cp, char* str)
{
	int n = 0;
	if (cp < 0x80) n = 1;
	else if (cp < 0x800) n = 2;
	else if (cp < 0x10000) n = 3;
	else if (cp < 0x200000) n = 4;
	else if (cp < 0x4000000) n = 5;
	else if (cp <= 0x7fffffff) n = 6;
	str[n] = '\0';
	switch (n) {
	case 6: str[5] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x4000000;
	case 5: str[4] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x200000;
	case 4: str[3] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x10000;
	case 3: str[2] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x800;
	case 2: str[1] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0xc0;
	case 1: str[0] = cp;
	}
	return str;
}

static void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	NVG_NOTUSED(scancode);
	NVG_NOTUSED(mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Menu::Menu() : _menu("PLAY\n\nSETTINGS\n\nQUIT"), _typeOfGame("1 VS 1\n\n1 VS IA\n\nIA vs IA\n\nEXIT"), _settingsText("EXIT")
{
  _init = true;
  _vg = NULL;
	_typeOfGameValue = 1;
  if (!glfwInit()) {
    cerr << "Failed to init GLFW." << endl;
    _init = false;
    return ;
  }
  // initGraph(&_fps, GRAPH_RENDER_FPS, "Frame Time");

  //set the callback function for all errors
  glfwSetErrorCallback(printErrorFunc);

  //Ask version of OpenGL supported max and min for the API
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  //If multi-samples compiled then we can use it
  #ifdef DEMO_MSAA
    glfwWindowHint(GLFW_SAMPLES, 4);
  #endif

  _window = glfwCreateWindow(1000, 600, "Gomoku", NULL, NULL);
  if (!_window) {
    glfwTerminate();
    _init = false;
    return ;
  }
  glfwSetKeyCallback(_window, key);
  glfwMakeContextCurrent(_window);

  //init graph lib for menu
  #ifdef NANOVG_GLEW
    if(glewInit() != GLEW_OK) {
      cerr << "Could not init glew." << endl;
      _init = false;
      return ;
    }
  #endif

  //depends on multi-samples activated or not
  #ifdef DEMO_MSAA
    _vg = nvgCreateGL2(NVG_STENCIL_STROKES | NVG_DEBUG);
  #else
    _vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
  #endif
  if (_vg == NULL) {
    cerr << "Could not init nanovg." << endl;
    _init = false;
    return ;
  }

  if (loadMenuData(_vg, &_data) == -1)
    {
      _init = false;
      return ;
    }
  if ((_backgroundImage = nvgCreateImage(_vg, "./assets/Menu/images/gomoku.jpg", 0)) == 0)
    {
      cerr << "Cannot load background." << endl;
      _init = false;
      return ;
    }

  // putinterval to refresh
  glfwSwapInterval(0);
  //set timer to 0
  glfwSetTime(0);

  _play = false;
  _settings = false;
  _quit = false;

	Sounds::get().playMusic("menu");
	_click = false;
	_options = true;

	_vectorOfGame.push_back("1 vs 1");
	_vectorOfGame.push_back("1 vs IA");
	_vectorOfGame.push_back("IA vs IA");
	_validate = false;
	_volume = 0.5f;
}

Menu::~Menu() {}

void 			Menu::endMenu()
{
	nvgDeleteImage(_vg, _backgroundImage);
  freeMenuData(_vg, &_data);
  nvgDeleteGL2(_vg);
  glfwTerminate();
}

int createParticles(GLFWwindow *window, int width, int height);

int 			Menu::resetValues()
{
	_play = false;
  _settings = false;
  _quit = false;
	Sounds::get().playMusic("menu");
	_click = true;
	_options = true;
	_typeOfGameValue = 1;
	_mouseClickPosX = -1;
	_mouseClickPosY = -1;
	_validate = false;
}

int        Menu::play()
{
	createParticles(_window, _windowWidth, _windowHeight);
  _previousTime = glfwGetTime();
  while (!glfwWindowShouldClose(_window))
    {
			if (_validate)
				return (_options ? _typeOfGameValue + 3 : _typeOfGameValue);
			if (_quit)
				return (-1);
      _mouseClickPosX = -1;
      _mouseClickPosY = -1;

      //get the fps and set value
      _timer = glfwGetTime();
      _duration = _timer - _previousTime;
      _previousTime = _timer;
      // updateGraph(&_fps, _duration);

      // get info about window and environment
      glfwGetCursorPos(_window, &_mousePosX, &_mousePosY);
      glfwGetWindowSize(_window, &_windowWidth, &_windowHeight);
      glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);

      float pxRatio;
      // Calculate pixel ration for hi-dpi devices.
      pxRatio = (float)_frameBufferWidth / (float)_windowWidth;

      // Update and render
      glViewport(0, 0, _frameBufferWidth, _frameBufferHeight);
      if (premult)
        glClearColor(0,0,0,0);
      else
        glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

      //begin update window
			int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
			if (state == GLFW_PRESS && !_click) {
      	_mouseClickPosX = _mousePosX;
      	_mouseClickPosY = _mousePosY;
				_click = true;
			} else if (state == GLFW_RELEASE) {
				_click = false;
			}
      nvgBeginFrame(_vg, _windowWidth, _windowHeight, pxRatio);

      //print background
      drawImg(_vg, 0, 0, _windowWidth, _windowHeight, _backgroundImage);
      // drawParagraph(_windowWidth / 2 - 50, _windowHeight / 2 - 50, 200, _play ? _typeOfGame : _settings ? _settingsText : _menu);
			int tmpX = ((_windowWidth / 2) - 250) < 0 ? 0 : (_windowWidth / 2) - 250;
			int tmpY = ((_windowHeight / 2) - 250) < 0 ? 0 : (_windowHeight / 2) - 250;
			drawWindow(_vg, "GOMOKU", tmpX, tmpY, ((_windowWidth) / 2), _windowHeight - (_windowHeight / 3));
			drawDropDown(_vg, strdup(_vectorOfGame[_typeOfGameValue - 1].c_str()), tmpX + 20, tmpY + 50, _windowWidth / 3, 28);
			int clicked = _mouseClickPosX > tmpX + 20 && _mouseClickPosX < (tmpX + 20 + _windowWidth / 3) && _mouseClickPosY >= tmpY + 50 && _mouseClickPosY < (tmpY + 78);
			if (clicked)
				++_typeOfGameValue;
			if (_typeOfGameValue > 3)
				_typeOfGameValue = 1;
			drawCheckBox(_vg, "RULES", tmpX + 20, tmpY, _windowWidth / 3, _windowWidth / 4, _options);
			clicked = _mouseClickPosX > tmpX + 20 && _mouseClickPosX < (tmpX + 20 + _windowWidth / 3) &&
								_mouseClickPosY >= tmpY + (int)(_windowWidth/4*0.5f)-8 && _mouseClickPosY < tmpY + (int)(_windowWidth/4*0.5f)+12;
			if (clicked)
				_options = !_options;
			drawSlider(_vg, _volume, tmpX + 20, tmpY + (int)(_windowWidth/4*0.5f)-8 + 40, _windowWidth / 3, 48);
			clicked = _mouseClickPosX > tmpX + 20 && _mouseClickPosX < (tmpX + 20 + _windowWidth / 3) &&
								_mouseClickPosY >= tmpY + (int)(_windowWidth/4*0.5f)-8 + 50 && _mouseClickPosY < tmpY + (int)(_windowWidth/4*0.5f)+62;
			if (clicked) {
				_volume = 0.0f;
				int cmpt = 0;
				int tmp = ((_windowWidth / 3) / 10) * 1;
				while (_mouseClickPosX - tmpX + 10 > tmp && cmpt != 10) {
					++cmpt;
					tmp = ((_windowWidth / 3) / 10) * (cmpt + 1);
				}
				_volume = 0.1f * cmpt;
				Mix_VolumeMusic(MIX_MAX_VOLUME * _volume);
			}
			drawButton(_vg, "PLAY", tmpX + 20, tmpY + (int)(_windowWidth/4*0.5f)-8 + 80, _windowWidth / 3, 28, nvgRGBA(0,96,128,255));
			clicked = _mouseClickPosX > tmpX + 20 && _mouseClickPosX < (tmpX + 20 + _windowWidth / 3) &&
								_mouseClickPosY >= tmpY + (int)(_windowWidth/4*0.5f)-8 + 80 && _mouseClickPosY < tmpY + (int)(_windowWidth/4*0.5f)-8 + 80 + 28;
			if (clicked)
				_validate = true;
			drawButton(_vg, "QUIT", tmpX + 20, tmpY + (int)(_windowWidth/4*0.5f)-8 + 120, _windowWidth / 3, 28, nvgRGBA(0,96,128,255));
			clicked = _mouseClickPosX > tmpX + 20 && _mouseClickPosX < (tmpX + 20 + _windowWidth / 3) &&
								_mouseClickPosY >= tmpY + (int)(_windowWidth/4*0.5f)-8 + 120 && _mouseClickPosY < tmpY + (int)(_windowWidth/4*0.5f)-8 + 120 + 28;
			if (clicked)
				_quit = true;
      //end update window
      nvgEndFrame(_vg);
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
  return (-1);
}

bool        Menu::isInit()
{
  return (_init);
}
