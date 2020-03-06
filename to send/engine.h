#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include "UTIL.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "StateManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "LevelManager.h"

#define WIDTH 1080
#define HEIGHT 640
#define FPS 60

class TextureManager;
class AudioManager;
class InputManager;
class StateManager;
class ObjectManager;
class UIManager;
class LevelManager;
class engine
{
private:
	engine();
	bool m_bRunning;
	Uint32 m_start, m_end, m_delta, m_fps;
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags); //this inits the engine and all systems involved
	void wake(); //records time of frame start
	void sleep(); //sleeps extra time
	void clean(); //cleans up the engine

public:
	static engine& getInstance();
	int run(); //runs the engine
	void quit(); //sets m_bRunning to false
	~engine();
};

