#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "imageload.h"
#include "systemlogger.h"

using namespace std;

ImageLoad::ImageLoad()
{
    step("[Image Load] Contructing.");
	m_renderer = NULL;
}

static ImageLoad* instance = NULL;

ImageLoad* 
ImageLoad::getInstance()
{
    loop("[Image Load] Getting Instance.");
	if (instance == NULL)
	{
        step("[Image Load] Using Constructor to Instance.");
		instance = new ImageLoad();
	}
		
	return instance;
}

void 
ImageLoad::releaseInstance()
{
    step("[Image Load] Releasing Instance.");
	delete instance;
}

void 
ImageLoad::setRenderer(SDL_Renderer* renderer)
{
    step("[Image Load] Setting Renderer.");
	m_renderer = renderer;
}


SDL_Texture* 
ImageLoad::loadImg(const string& path)
{
    step("[Image Load] Loading Image.");

	if (m_renderer == NULL)
	{
		return NULL;
	}
	
	SDL_Surface* surface = IMG_Load( path.c_str() );

    if( surface == NULL )
    {
        step("[Image Load] Null Surface.");
        cout << SDL_GetError() << endl;
        throw "Impossível carregar a imagem!";
    }

    SDL_SetColorKey (surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFA, 0xCF, 0xAC));

    SDL_Texture* texture = SDL_CreateTextureFromSurface( m_renderer, surface );

    if( texture == NULL )
    {
        step("[Image Load] Null Texture.");
    	SDL_FreeSurface(surface);
    	throw "Impossível criar a textura!";
    }

    return texture;
}

void 
ImageLoad::release(SDL_Texture* texture)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}

void
ImageLoad::update(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
    SDL_RenderCopy( m_renderer, texture, srcRect, destRect);
}

void
ImageLoad::render()
{
    SDL_RenderPresent( m_renderer );
    SDL_RenderClear ( m_renderer );
}