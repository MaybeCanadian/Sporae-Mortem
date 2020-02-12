#pragma once
#include "basic_includes.h"
#include "Engine.h"
class TextureManager
{
private:
	TextureManager();
	vector<SDL_Texture*> textures;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
public:
	~TextureManager();
	static TextureManager& getInstance();
	int addTexture(string texture); //loads the texture to the vector and returns the id the texture is stored at
	bool createRenderer();
	bool createWindow(const char* title, int xpos, int ypos, int width, int height, int flags);
	void clean();
	void Draw(const int textureID, const SDL_Rect* position, const SDL_Rect* area, const double rotation, const SDL_Rect* centre, const SDL_RendererFlip flip);
	void RenderPresent();
	void DrawBacking(const int textureID);
};

