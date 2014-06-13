#include "text.h"

Text::Text(const string& fontPath, int fontSize)
{
	m_font = TTF_OpenFont(fontPath.c_str(),fontSize);
	if(!m_font)
	{
		step(fontPath);
		cout << fontSize << endl;
		errorSDL("[Text] Null Font.", TTF_GetError());
	}
	m_fontColor = {255,255,255,255};
	m_textNumber = 0;
	m_positionNumber = 0;
}

Text::~Text()
{
	TTF_CloseFont(m_font);
}

void
Text::addText(const string& newText)
{
	m_texts.push_back(newText);
}
void
Text::removeText()
{
	m_texts.erase(m_texts.begin()+1);
}

void
Text::setTextNumber(int newTextNumber)
{
	m_textNumber = newTextNumber;
}

void
Text::addPosition(int x, int y)
{
	SDL_Rect newPosition = {x,y,0,0};
	m_positions.push_back(newPosition);
}

void
Text::setPositionNumber(int newPositionNumber)
{
	m_positionNumber = newPositionNumber;
}

void
Text::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color newColor = {r,g,b,a};
	m_fontColor = newColor;
}

void
Text::drawText()
{
	SDL_Surface* renderedText = TTF_RenderText_Blended(m_font, m_texts.at(m_textNumber).c_str(), m_fontColor);
	if(!renderedText)
	{
		errorSDL("[Text] Null Texture.",SDL_GetError());
	}
	SDL_Texture* textureText = surfaceToTexture(renderedText);
	if(!textureText)
	{
		errorSDL("[Text] Null Texture.",SDL_GetError());
	}
	SDL_QueryTexture(textureText,NULL,NULL,&m_positions.at(m_positionNumber).w,&m_positions.at(m_positionNumber).h);
	imageDraw(textureText, NULL, &m_positions.at(m_positionNumber));
}