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
	_typeOfGameValue = -1;
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
	_options = false;
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
	_options = false;
	_typeOfGameValue = -1;
	_mouseClickPosX = -1;
	_mouseClickPosY = -1;
}

int        Menu::play()
{
	createParticles(_window, _windowWidth, _windowHeight);
  _previousTime = glfwGetTime();
  while (!glfwWindowShouldClose(_window))
    {
			if (_typeOfGameValue != -1)
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
      drawImg(0, 0, _windowWidth, _windowHeight, _backgroundImage);
      drawParagraph(_windowWidth / 2 - 50, _windowHeight / 2 - 50, 200, _play ? _typeOfGame : _settings ? _settingsText : _menu);

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

void 	Menu::drawCheckBox(const char* text, float x, float y, float w, float h)
{
	NVGpaint bg;
	char icon[8];
	NVG_NOTUSED(w);

	nvgFillColor(_vg, nvgRGBA(255,255,255,255));

	nvgTextAlign(_vg,NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
	nvgText(_vg, x+28,y+h*0.5f,text, NULL);

	bg = nvgBoxGradient(_vg, x+1,y+(int)(h*0.5f)-9+1, 18,18, 3,3, nvgRGBA(255,255,255,32), nvgRGBA(255,255,255,255));
	nvgBeginPath(_vg);
	nvgRoundedRect(_vg, x+1,y+(int)(h*0.5f)-9, 18,18, 3);
	nvgFillPaint(_vg, bg);
	nvgFill(_vg);

	if (_options) {
		nvgFontSize(_vg, 40);
		nvgFontFace(_vg, "icons");
		nvgFillColor(_vg, nvgRGBA(255,255,255,255));
		nvgTextAlign(_vg,NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);
		nvgText(_vg, x+9+2, y+h*0.5f, cpToUTF8(ICON_CHECK,icon), NULL);
	}
}

int         Menu::drawImg(int posX, int posY, int width, int height, int refImg)
{
  int       saveX;
  int       saveY;
  NVGpaint  imgPaint;


  saveX = width;
  saveY = height;
  nvgImageSize(_vg, refImg, &saveX, &saveY);
  imgPaint = nvgImagePattern(_vg, posX, posY, width, height, 0, refImg, 1);
  nvgBeginPath(_vg);
  nvgRoundedRect(_vg, posX, posY, width, height, 0);
  nvgFillPaint(_vg, imgPaint);
  nvgFill(_vg);
  return (0);
}

int             Menu::drawParagraph(float x, float y, float width, const char *text)
{
	NVGtextRow    rows[3];
	const char*   start;
	const char*   end;
	int           nrows;
  int           i;
	float         lineh;
  int           pos;

	nvgSave(_vg);
	nvgFontSize(_vg, 38.0f);
	nvgFontFace(_vg, "sans");
	nvgTextAlign(_vg, NVG_ALIGN_LEFT|NVG_ALIGN_TOP);
	nvgTextMetrics(_vg, NULL, NULL, &lineh);

	start = text;
	end = text + strlen(text);
  pos = 0;
	if (_settings) {
		drawCheckBox("RULES", x, y - 50, width, width);
		nvgFontFace(_vg, "sans");
		nvgTextAlign(_vg, NVG_ALIGN_LEFT|NVG_ALIGN_TOP);
		nvgTextMetrics(_vg, NULL, NULL, &lineh);
		y += (lineh * 2);
		if (_mouseClickPosX > x && _mouseClickPosX < (x + width) && _mouseClickPosY >= y - 50 && _mouseClickPosY < (y - 50 + lineh))
			_options = !_options;
	}
	while ((nrows = nvgTextBreakLines(_vg, start, end, width, rows, 3))) {
		for (i = 0; i < nrows; i++) {
			NVGtextRow* row = &rows[i];
      int hit = _mousePosX > x && _mousePosX < (x + width) && _mousePosY >= y && _mousePosY < (y + lineh);
			int clicked = _mouseClickPosX > x && _mouseClickPosX < (x + width) && _mouseClickPosY >= y && _mouseClickPosY < (y + lineh);
			nvgBeginPath(_vg);
      if (row->width != 0)
        {
          ++pos;
          nvgFillColor(_vg, nvgRGBA(255,255,255,hit?64:0));
    			nvgRect(_vg, x, y, row->width, lineh);
    			nvgFill(_vg);
        }
			nvgFillColor(_vg, nvgRGBA(255,255,255,255));
			nvgText(_vg, x, y, row->start, row->end);
			y += lineh;
			if (_click) {
				if (!_play && !_settings) {
		      if (clicked && pos == 1)
		        _play = true;
		      else if (clicked && pos == 2)
		        _settings = true;
		      else if (clicked && pos == 3)
		        _quit = true;
				} else if (_play) {
					if (clicked && (pos == 1 || pos == 2 || pos == 3))
		        _typeOfGameValue = pos;
					else if (clicked && pos == 4)
				    _play = false;
				} else if (_settings) {
					if (clicked && pos == 1) {
						_settings = false;
					}
				}
			}
		}
		start = rows[nrows-1].next;
	}
	nvgRestore(_vg);
  return (0);
}