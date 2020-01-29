#include "Engine.h"
using namespace std;


Engine::Engine()
{
	m_bRunning = false; 
	cout << "constructed..." << endl;
}
Engine::~Engine(){}

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
}

bool Engine::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				m_pTexture = IMG_LoadTexture(m_pRenderer, "tree.png");
				b_pTexture = IMG_LoadTexture(m_pRenderer, "sky.png");
				cout << (int)SDL_NumJoysticks << endl;
			/*	if (SDL_NumJoysticks > 0)
				{
					joystic_deadzone = 8000;
					for (int i = 0; i < 4; i++)
					{

					}
					cout << SDL_NumJoysticks << " joysticks connected" << endl;
					for (int i = 0; i < (int)SDL_NumJoysticks || i > 4; i++)
					{

					}*/
				//}
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_bRunning = true; // Everything is okay, start the engine.
	numPlayers = 1;
	for (int i = 0; i < numPlayers; i++)
	{
		m_pPlayers[i] = new Player();
	}
	binds[0] = SDL_SCANCODE_UP;
	binds[1] = SDL_SCANCODE_DOWN;
	binds[2] = SDL_SCANCODE_LEFT;
	binds[3] = SDL_SCANCODE_RIGHT;
	cout << "Success!" << endl;
	return true;
}

void Engine::wake()
{
	m_start = SDL_GetTicks();
}

void Engine::sleep()
{ 
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

bool Engine::keyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}


void Engine::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_bRunning = false;
			break;
		}
	}
}

void Engine::update()
{
	for (int i = 0; i < numPlayers; i++)
		m_pPlayers[i]->update();
//	b_pSky->update();
}

void Engine::render()
{
SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
// Clear the screen with the draw color.
	for (int i = 0; i < numPlayers; i++)
		SDL_RenderCopyEx(m_pRenderer, m_pTexture, NULL, &(m_pPlayers[i]->getRect()), (m_pPlayers[i]->getRotation() - 90), NULL, SDL_FLIP_NONE);
	// Draw anew.
	SDL_RenderPresent(m_pRenderer);
}

void Engine::clean()
{
	cout << "Cleaning game." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	for (int i = 0; i < numPlayers; i++)
		delete(m_pPlayers[i]);
	SDL_Quit();
}

int Engine::run()
{
	if (init("GAME1007_SDL_Setup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning)
	{
		wake();
		handleEvents();
		update();
		render();
		if (m_bRunning)
			sleep();
	}
	clean();
	return 0;
}
