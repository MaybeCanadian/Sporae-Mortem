#include "TextureManager.h"
#include "basic_includes.h"


TextureManager::TextureManager()
{
	m_pRenderer = NULL;
	m_pWindow = NULL;
}

TextureManager::~TextureManager()
{
}

TextureManager & TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

bool TextureManager::createRenderer()
{
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	if (m_pRenderer != NULL)
		return true;
	else
		return false;
}

bool TextureManager::createWindow(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (m_pWindow != NULL)
		return true;
	else
		return false;
}

void TextureManager::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	for (int i = 0 ; i < (int)textures.size(); i++)
		SDL_DestroyTexture(textures[i]);
}

void TextureManager::Draw(const int textureID, const SDL_Rect* position, const SDL_Rect* area, const double rotation, const SDL_Rect* centre, const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(m_pRenderer, textures[textureID], NULL, position, rotation, NULL, flip);
}

void TextureManager::RenderPresent()
{
	SDL_RenderPresent(m_pRenderer);
}

void TextureManager::DrawBacking(const int textureID)
{
	SDL_RenderCopy(m_pRenderer, textures[textureID], NULL, NULL);
}

int TextureManager::addTexture(string texture)
{
	SDL_Texture *textureBuffer;
	const char* charBuffer = texture.c_str();
	textureBuffer =  IMG_LoadTexture(m_pRenderer, charBuffer);
	textures.push_back(textureBuffer);
	return ((int)textures.size() - 1);
}

