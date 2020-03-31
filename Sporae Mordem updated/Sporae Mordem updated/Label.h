#pragma once
#ifndef __Label__
#define __Label__

#include <string>

#include "FontManager.h"
class FontManager;
class Label
{
public:
	Label(std::string text = "Default Label Text", std::string fontName = "lazy", int size = 20, SDL_Color colour = { 0, 0, 0, 255 }, std::vector<int> position = { 0,0 }, int fontStyle = TTF_STYLE_NORMAL, bool isCentered = true);
	~Label();

	// Inherited via GameObject
	void render();
	void update();
	void clean();

	void setText(std::string newText);
	void setColour(SDL_Color newColour);
	void setSize(int newSize);

private:
	SDL_Rect m_dst;
	std::string m_fontPath;
	std::string m_fontID;
	SDL_Color m_fontColour;
	std::string m_fontName;
	std::string m_text;
	bool m_isCentered = true;
	int m_fontSize;
	int m_fontStyle;
	int textureID;
	void m_buildFontID();
};

#endif /* defined (__Label__) */