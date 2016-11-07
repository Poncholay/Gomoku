/*
** Menu.cpp for Gomoku in /home/wilmot_g/Epitech/IA/Gomoku/src/Menu
**
** Made by cheesy shift
** Login   <saurs_f@epitech.net>
**
** Started on  Mon Nov 07 22:35:02 2016 saurs_f
** Last update Mon Nov 07 22:35:47 2016 wilmot_g
*/

#include "Menu.hh"
#include "nanovg.h"
#include "nanovg_gl.h"
#include "Sounds.hpp"

using namespace std;

int blowup = 0;
int screenshot = 0;
int premult = 0;

void printErrorFunc(int error, const char *desc)
{
	cerr << "GLFW error " << error << ": " << desc << endl;
}

static void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	NVG_NOTUSED(scancode);
	NVG_NOTUSED(mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		blowup = !blowup;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		screenshot = 1;
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		premult = !premult;
}

Menu::Menu() : _menu("PLAY\n\nSETTINGS\n\nQUIT"), _typeOfGame("1 VS 1\n\n1 VS IA\n\nIA vs IA\n\nEXIT")
{
  _init = true;
  _vg = NULL;
  if (!glfwInit()) {
    cerr << "Failed to init GLFW." << endl;
    _init = false;
    return ;
  }
  initGraph(&_fps, GRAPH_RENDER_FPS, "Frame Time");

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
}

Menu::~Menu() {}

void 			Menu::endMenu()
{
	nvgDeleteImage(_vg, _backgroundImage);
  freeMenuData(_vg, &_data);
  nvgDeleteGL2(_vg);
  glfwTerminate();
}

int        Menu::play()
{
  _previousTime = glfwGetTime();
  while (!glfwWindowShouldClose(_window))
    {
			if (_play)
				return (0);
			else if (_quit)
				return (-1);
      _mouseClickPosX = -1;
      _mouseClickPosY = -1;
//      cout << "play " << _play << " settings " << _settings << " quit " << _quit << endl;
      //get the fps and set value
      _timer = glfwGetTime();
      _duration = _timer - _previousTime;
      _previousTime = _timer;
      updateGraph(&_fps, _duration);

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
      if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT))
        {
          _mouseClickPosX = _mousePosX;
          _mouseClickPosY = _mousePosY;
        }
      nvgBeginFrame(_vg, _windowWidth, _windowHeight, pxRatio);

      //print background
      drawImg(0, 0, _windowWidth, _windowHeight, _backgroundImage);
      drawParagraph(_windowWidth / 2 - 50, _windowHeight / 2 - 50, 200, _play ? _typeOfGame : _menu);

        //renderDemo(_vg, _mousePosX, _mousePosY, _windowWidth, _windowHeight, _timer, blowup, &_data);
      //      renderGraph(_vg, 5, 5, &_fps);

      //end update window
      nvgEndFrame(_vg);
      if (screenshot)
        {
          screenshot = 0;
          saveScreenShot(_frameBufferWidth, _frameBufferHeight, premult, "dump.png");
        }
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }
  return (-1);
}

bool        Menu::isInit()
{
  return (_init);
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
      if (clicked && pos == 1)
        _play = true;
      else if (clicked && pos == 2)
        _settings = true;
      else if (clicked && pos == 3)
        _quit = true;
		}
		start = rows[nrows-1].next;
	}
	nvgRestore(_vg);
  return (0);
}
