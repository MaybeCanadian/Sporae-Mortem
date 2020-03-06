#pragma once
#include "engine.h"
#include <SDL_image.h>

class TextureManager
{
private:
	std::vector<SDL_Texture*> textures;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

private:
	void SetBlendMode();
	TextureManager();

public:
	~TextureManager();
	static TextureManager& getInstance();
	int addTexture(std::string texture); //loads the texture to the vector and returns the id the texture is stored at
	bool initManager(const char* title, int xpos, int ypos, int width, int height, int flags);
	void clean();
	void DrawEx(const int textureID, const SDL_Rect* position, const SDL_Rect* area, const double rotation, const SDL_Rect* centre, const SDL_RendererFlip flip);
	void Draw(const int textureID, const SDL_Rect* position, const SDL_Rect* area);
	void RenderPresent();
	void DrawBacking(const int textureID);
	void SetDrawColor(Uint8, Uint8, Uint8, Uint8);
	void FillRect(SDL_Rect* rect);
	void RenderClear();
};