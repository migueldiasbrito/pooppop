#include "ImageCache.h"
#include <iostream>

namespace engine = ::pooppop::sdl_game_engine;

SDL_Surface* engine::ImageCache::LoadImage(std::string filename)
{
	std::map<std::string, SDL_Surface*>::iterator it = imageCache.find(filename);
	SDL_Surface* rawImage;

	if (it == imageCache.end())
	{
		rawImage = IMG_Load(filename.c_str());

		if (rawImage == NULL)
		{
			std::cout << "Unable to load image " << filename.c_str()
				<< "! SDL_image Error: " << IMG_GetError() << std::endl;
			return NULL;
		}
		else
		{
			imageCache.insert(std::pair<std::string, SDL_Surface*>(filename, rawImage));
		}
	}
	else
	{
		rawImage = it->second;
	}

	return rawImage;
}

void engine::ImageCache::Close()
{
	std::map<std::string, SDL_Surface*>::iterator it = imageCache.begin();
	for (; it != imageCache.end(); it++)
	{
		SDL_FreeSurface(it->second);
		it->second = NULL;
	}
}
