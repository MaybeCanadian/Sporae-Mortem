#include "engine.h"

int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	return engine::getInstance().run();
}