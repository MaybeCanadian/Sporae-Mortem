#pragma once
#include "Player.h"
#include "Map.h"
#include "basic_includes.h"
#include "SoundManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
// Keep header clean of initializaions and function definitions.
// Method prototypes only.
class Player;
class sky;
class SoundManager;
class ObjectManager;
class TextureManager;
class Map;
class Engine
{
private: // Properties.
	bool m_bRunning; // Loop control flag.
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Joystick* m_pController[4];
	int joystic_deadzone;
	Player* m_pPlayers[4];
	int floorID, EnemyID;
	int numPlayers;
	sky* b_pSky;
	SDL_Scancode binds[4];
	Map* m_pMap;
	Enemy* m_pEnemy;
private: // Methods.
	bool init(const char*, int, int, int, int, int); // Parameter names are not needed in a function prototype.
	void wake(); // Function prototypes ARE statements, so don't forget the ';'
	void sleep(); //put sleep back in cpp file
	void handleEvents();
	void update();
	void render();
	void clean();
	Engine();
public:
	
	~Engine();
	static Engine& getInstance();
	bool keyDown(SDL_Scancode c);
	int run();
};

