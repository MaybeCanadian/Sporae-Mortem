#pragma once
#ifndef __FontManager__
#define __FontManager__

#include <SDL_ttf.h>
#include "engine.h"

class FontManager 
{
private:
	std::unordered_map<std::string, TTF_Font*> m_fontMap;

private:
	FontManager();
public:
	static FontManager& getInstance();
	bool initManager();
	bool load(std::string fileName, std::string id, int size, int style = TTF_STYLE_NORMAL);
	bool textToTexture(std::string text, std::string fontID,int& textureID, SDL_Color colour = { 0, 0, 0, 255 });
	TTF_Font* getFont(std::string id);
	void clean();
	~FontManager();
};


#endif /* defined(__FontManager__) */
