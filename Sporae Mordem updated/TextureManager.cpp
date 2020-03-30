#include "TextureManager.h"

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

void TextureManager::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	textures.clear();
	textures.shrink_to_fit();
	std::cout << "textureManager clean.\n";
}

void TextureManager::DrawEx(const int textureID, const SDL_Rect* position, const SDL_Rect* area, const double rotation, const SDL_Point* centre, const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(m_pRenderer, textures[textureID], area, position, rotation, centre, flip);
}

void TextureManager::RenderPresent()
{
	SDL_RenderPresent(m_pRenderer);
}

void TextureManager::DrawBacking(const int textureID)
{
	SDL_RenderCopy(m_pRenderer, textures[textureID], NULL, NULL);
}

void TextureManager::SetBlendMode()
{
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
}

void TextureManager::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void TextureManager::FillRect(SDL_Rect* rect)
{
	SDL_RenderFillRect(m_pRenderer, rect);
}

void TextureManager::FillCircle(SDL_Point * pos, double radius) //makes a rect for now
{
	SDL_Rect buffer = { pos->x, pos->y, radius * 2 , radius * 2 };
	FillRect(&buffer);
}

void TextureManager::RenderClear()
{
	SDL_RenderClear(m_pRenderer);
}

void TextureManager::Draw(const int textureID, const SDL_Rect* src, const SDL_Rect* dst)
{
	SDL_RenderCopy(m_pRenderer, textures[textureID], src, dst);
}

int TextureManager::addTexture(std::string texture)
{
	SDL_Texture *textureBuffer;
	const char* charBuffer = texture.c_str();
	textureBuffer = IMG_LoadTexture(m_pRenderer, charBuffer);
	textures.push_back(textureBuffer);
	return ((int)textures.size() - 1);
}

int TextureManager::addTexture(SDL_Surface* textSurface)
{
	SDL_Texture* textureBuffer;
	textureBuffer = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);
	textures.push_back(textureBuffer);
	return ((int)textures.size() - 1);
}

std::vector<int> TextureManager::getTextureSize(int id)
{
	int width, height;
	SDL_QueryTexture(textures[id], NULL, NULL, &width, &height);
	std::vector<int> size;

	size[0] = width;
	size[1] = height;

	return size;
}

SDL_Texture* TextureManager::getTexture(int id)
{
	return textures[id];
}

bool TextureManager::initManager(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (m_pWindow != NULL)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		if (m_pRenderer != NULL)
		{
			SetBlendMode();
			std::cout << "textureManager init.\n";
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

