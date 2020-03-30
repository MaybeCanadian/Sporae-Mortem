#include "Label.h"

Label::Label(std::string text, std::string fontName, int fontSize, SDL_Color colour, std::vector<int> position, int fontStyle, bool isCentered) :
	m_fontName(fontName), m_fontColour(colour), m_text(text), m_isCentered(isCentered), m_fontSize(fontSize), m_fontStyle(fontStyle)
{

	m_fontPath = "fonts/" + fontName + ".ttf";

	m_buildFontID();

	FontManager::getInstance().load(m_fontPath, m_fontID, fontSize, fontStyle);

	if (FontManager::getInstance().textToTexture(text, m_fontID, textureID, colour))
	{
		SDL_Point* size = TextureManager::getInstance().getTextureSize(textureID);
		m_dst.w = size->x;
		m_dst.h = size->y;
		m_dst.x = position[0];
		m_dst.y = position[1];
	}
	else
	{
		std::cout << "error making label.\n";
	}
}

Label::~Label()
{

}

void Label::render()
{
	TextureManager::getInstance().Draw(textureID,NULL,&m_dst);
}

void Label::update()
{
}

void Label::clean()
{

}

void Label::setText(std::string newText)
{

	m_text = newText;

	m_buildFontID();

	FontManager::getInstance().load(m_fontPath, m_fontID, m_fontSize, m_fontStyle);

	FontManager::getInstance().textToTexture(newText, m_fontID, textureID, m_fontColour);
	SDL_Point* size = TextureManager::getInstance().getTextureSize(textureID);
	m_dst.w = size->x;
	m_dst.h = size->y;
}

void Label::setColour(SDL_Color newColour)
{
	FontManager::getInstance().load(m_fontPath, m_fontID, m_fontSize, m_fontStyle);
	FontManager::getInstance().textToTexture(m_text, m_fontID, textureID, newColour);
}

void Label::setSize(int newSize)
{
	m_fontSize = newSize;

	m_buildFontID();
	
	FontManager::getInstance().load(m_fontPath, m_fontID, m_fontSize);

	FontManager::getInstance().textToTexture(m_text, m_fontID, textureID, m_fontColour);
	SDL_Point* size = TextureManager::getInstance().getTextureSize(textureID);
	m_dst.w = size->x;
	m_dst.h = size->y;
}

void Label::m_buildFontID()
{
	m_fontID = m_fontName;
	m_fontID += "-";
	m_fontID += std::to_string(m_fontSize);
	m_fontID += "-";
	m_fontID += m_text;

	std::cout << "fontID: " << m_fontID << std::endl;
	/*std::cout << "TextureMap Size: " << FontManager::getInstance().getTextureMapSize() << std::endl;*/
}

