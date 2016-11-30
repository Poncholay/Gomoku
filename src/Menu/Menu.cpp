/*
** Menu.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src/Menu
**
** Made by cheesy shift
** Login   <saurs_f@epitech.net>
**
** Started on  Mon Nov 07 22:35:02 2016 saurs_f
** Last update Wed Nov 23 21:57:14 2016 wilmot_g
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

void printErrorFunc(int error, const char *desc) {cerr << "GLFW error " << error << ": " << desc << endl;}

static void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	NVG_NOTUSED(scancode);
	NVG_NOTUSED(mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Menu::Menu() {
  _init = true;
  _vg = NULL;
	if (!glfwInit()) {
    cerr << "Failed to init GLFW." << endl;
    _init = false;
    return ;
  }
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
  if (loadMenuData(_vg, &_data) == -1) {
      _init = false;
      return ;
    }
  if ((_backgroundImage = nvgCreateImage(_vg, "./assets/Menu/images/gomoku.jpg", 0)) == 0) {
      cerr << "Cannot load background." << endl;
      _init = false;
      return ;
    }
  // putinterval to refresh
  glfwSwapInterval(0);
  //set timer to 0
  glfwSetTime(0);
	Sounds::get().playMusic("menu");
	_click = false;
	_quit = false;
	_vectorOfGame.push_back("1 vs 1");
	_vectorOfGame.push_back("1 vs IA");
	_vectorOfGame.push_back("IA vs IA");
	_validate = false;
	_testOfTextBox.push_back("RULES");
	_testOfTextBox.push_back("BENCHMARK");
	_testOfTextBox.push_back("MAP SIZE ADAPTATION");
	_testOfTextBox.push_back("ONLY ACTIVE SPOTS");
	_testOfTextBox.push_back("ROWS");
	_testOfTextBox.push_back("DIAGONALS");
}

Menu::~Menu() {
	nvgDeleteImage(_vg, _backgroundImage);
	freeMenuData(_vg, &_data);
	nvgDeleteGL2(_vg);
	glfwTerminate();
}

bool	*Menu::getRules() const {
	return _choices;
}

float Menu::getVolume() const {
	return _volume;
}

bool Menu::isInit() {return (_init);}

void 			Menu::setValues(int typeOfGameValue, float volume, bool *choices) {
	_volume = volume;
	_typeOfGameValue = typeOfGameValue;
	_choices = choices;
	_selected = false;
}

void 			Menu::drawBackGround() {
	drawImg(_vg, 0, 0, _windowWidth, _windowHeight, _backgroundImage);
	_tmpX = ((_windowWidth / 2) - 250) < 0 ? 0 : (_windowWidth / 2) - 250;
	_tmpY = ((_windowHeight / 2) - 250) < 0 ? 0 : (_windowHeight / 2) - 250;
	drawWindow(_vg, "GOMOKU", _tmpX, _tmpY, ((_windowWidth) / 2), _windowHeight - (_windowHeight / 3));
}

void 		Menu::setWindowAndVar() {
	_mouseClickPosX = -1;
	_mouseClickPosY = -1;
	//get the fps and set value
	_timer = glfwGetTime();
	_duration = _timer - _previousTime;
	_previousTime = _timer;
	// get info about window and environment
	glfwGetCursorPos(_window, &_mousePosX, &_mousePosY);
	glfwGetWindowSize(_window, &_windowWidth, &_windowHeight);
	glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);
	// Calculate pixel ration for hi-dpi devices.
	_pxRatio = (float)_frameBufferWidth / (float)_windowWidth;
	// Update and render
	glViewport(0, 0, _frameBufferWidth, _frameBufferHeight);
	if (premult)
		glClearColor(0,0,0,0);
	else
		glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void 			Menu::detectClick() {
	int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS && !_click) {
		_mouseClickPosX = _mousePosX;
		_mouseClickPosY = _mousePosY;
		_click = true;
	} else if (state == GLFW_RELEASE) {
		_click = false;
	}
}

void 			Menu::detectInput() {
	// int state = glfwGetKey(_window, GLFW_MOUSE_BUTTON_LEFT);
	// if (state == GLFW_PRESS && !_click) {
	// } else if (state == GLFW_RELEASE) {
	// }
}
void 				Menu::checkTypeOfGame() {
	drawDropDown(_vg, strdup(_vectorOfGame[_typeOfGameValue - 1].c_str()), _tmpX + 20, _tmpY + 50, _windowWidth / 3, 28);
	_clicked = _mouseClickPosX > _tmpX + 20 && _mouseClickPosX < (_tmpX + 20 + _windowWidth / 3) && _mouseClickPosY >= _tmpY + 50 && _mouseClickPosY < (_tmpY + 78);
	if (_clicked)
		++_typeOfGameValue;
	if (_typeOfGameValue > 3)
		_typeOfGameValue = 1;
}

void Menu::drawAllCheckBox() {
	_pos = -25;
	int index = 0;
	for (auto it : _testOfTextBox) {
		drawCheckBoxWithText(it, index++);
		_pos += 25;
	}
	_pos -= 50;
}

void 			Menu::drawCheckBoxWithText(string text, int index) {
	drawCheckBox(_vg, text.c_str(), _tmpX + 20, _tmpY + _pos, _windowWidth / 3, _windowWidth / 4, _choices[index]);
	_clicked = _mouseClickPosX > _tmpX + 20 && _mouseClickPosX < (_tmpX + 20 + _windowWidth / 3) &&
						_mouseClickPosY >= _tmpY + _pos+ (int)(_windowWidth/4*0.5f)-8 && _mouseClickPosY < _tmpY + _pos+ (int)(_windowWidth/4*0.5f)+12;
	if (_clicked)
		_choices[index] = !_choices[index];
}

void 			Menu::checkControlSound() {
	drawSlider(_vg, _volume, _tmpX + 20, _tmpY + _pos+ (int)(_windowWidth/4*0.5f)-8 + 40, _windowWidth / 3, 48);
	_clicked = _mouseClickPosX > _tmpX + 20 && _mouseClickPosX < (_tmpX + 20 + _windowWidth / 3) &&
						_mouseClickPosY >= _tmpY + _pos+ (int)(_windowWidth/4*0.5f)-8 + 50 && _mouseClickPosY < _tmpY + _pos+ (int)(_windowWidth/4*0.5f)+62;
	if (_clicked) {
		_volume = 0.0f;
		int cmpt = 0;
		int tmp = ((_windowWidth / 3) / 10) * 1;
		while (_mouseClickPosX - _tmpX + 10 > tmp && cmpt != 10) {
			++cmpt;
			tmp = ((_windowWidth / 3) / 10) * (cmpt + 1);
		}
		_volume = 0.1f * cmpt;
		Mix_VolumeMusic(MIX_MAX_VOLUME * _volume);
	}
}

void 				Menu::checkButtons() {
	drawButton(_vg, "PLAY", _tmpX + 20, _tmpY + _pos + (int)(_windowWidth/4*0.5f)-8 + 80, _windowWidth / 3, 28, nvgRGBA(0,96,128,255));
	_clicked = _mouseClickPosX > _tmpX + 20 && _mouseClickPosX < (_tmpX + 20 + _windowWidth / 3) &&
						_mouseClickPosY >= _tmpY + _pos+ (int)(_windowWidth/4*0.5f)-8 + 80 && _mouseClickPosY < _tmpY + _pos + (int)(_windowWidth/4*0.5f)-8 + 80 + 28;
	if (_clicked)
		_validate = true;
	drawButton(_vg, "QUIT", _tmpX + 20, _tmpY + _pos + (int)(_windowWidth/4*0.5f)-8 + 120, _windowWidth / 3, 28, nvgRGBA(0,96,128,255));
	_clicked = _mouseClickPosX > _tmpX + 20 && _mouseClickPosX < (_tmpX + 20 + _windowWidth / 3) &&
						_mouseClickPosY >= _tmpY + _pos+ (int)(_windowWidth/4*0.5f)-8 + 120 && _mouseClickPosY < _tmpY + _pos + (int)(_windowWidth/4*0.5f)-8 + 120 + 28;
	if (_clicked)
		_quit = true;
}

int        Menu::play() {
  _previousTime = glfwGetTime();
  while (!glfwWindowShouldClose(_window))
    {
			if (_validate)
				return (_typeOfGameValue);
			if (_quit)
				return (-1);

			setWindowAndVar();
			detectClick();
			detectInput();

      nvgBeginFrame(_vg, _windowWidth, _windowHeight, _pxRatio);

			drawBackGround();

			checkTypeOfGame();

			drawAllCheckBox();

			checkControlSound();
			checkButtons();

			drawEditBox(_vg, "3", _tmpX + 20, _tmpY + _pos + 50 + (int)(_windowWidth/4*0.5f)-8 + 120,  _windowWidth / 3, 28);
			_clicked = _mouseClickPosX > _tmpX + 20 && _mouseClickPosX < (_tmpX + 20 + _windowWidth / 3) &&
								_mouseClickPosY >= _tmpY + _pos + 50 + (int)(_windowWidth/4*0.5f)-8 + 120 && _mouseClickPosY < _tmpY + _pos + 50 + (int)(_windowWidth/4*0.5f)-8 + 120 + 28;
			if (_clicked)
				_selected = true;

      nvgEndFrame(_vg);
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
  return (-1);
}
