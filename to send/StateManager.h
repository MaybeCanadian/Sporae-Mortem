#pragma once
#include "engine.h"
#include "State.h"

class State;
class StateManager
{
private:
	int state;

private:
	StateManager();
	void switchState(int newState); //exits old state, changes current state, enters new state
public:
	static StateManager& getInstance();
	int getState(); //returns the current state
	void changeState(int input); //puts in a change request
	bool initManager(); //inits the manager
	void clean(); //cleans the manager
	void update(); //updates the current state
	void render(); //renders the current state
	void handleEvents(); //handles events for current state
	~StateManager();
};

