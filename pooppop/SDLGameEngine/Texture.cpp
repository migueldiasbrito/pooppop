#include "Texture.h"
#include <iostream>

namespace engine = ::pooppop::sdl_game_engine;

engine::Texture::Texture(SDL_Surface* image, SDL_Renderer* gRenderer) :
	context(gRenderer)
{
	myTexture = SDL_CreateTextureFromSurface(gRenderer, image);

	if (myTexture == NULL)
	{
		std::cout << "Unable to create texture! SDL Error: " << SDL_GetError()
			<< std::endl;
	}

}

engine::Texture::~Texture()
{
	SDL_DestroyTexture(myTexture);
}

void engine::Texture::Close()
{
	SDL_DestroyTexture(myTexture);
}

void engine::Texture::DrawAt(int x, int y, int w, int h)
{
	SDL_Rect fillRect;

	if (w < 0 || h < 0)
	{
		SDL_GetRendererOutputSize(context, &w, &h);
	}

	fillRect = { x, y, w, h };

	SDL_RenderCopy(context, myTexture, NULL, &fillRect);
}

void engine::Texture::SetBlendMode(bool blending)
{
	SDL_BlendMode blendMode;

	if (blending)
	{
		blendMode = SDL_BLENDMODE_BLEND;
	}
	else
	{
		blendMode = SDL_BLENDMODE_NONE;
	}
	SDL_SetTextureBlendMode(myTexture, blendMode);
}

void engine::Texture::ManipulateColors(float red, float blue, float green)
{
	SDL_SetTextureColorMod(myTexture, red, green, blue);
}

void engine::Texture::ManipulateAlpha(float alpha)
{
	SDL_SetTextureAlphaMod(myTexture, alpha);
}
