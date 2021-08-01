#include "Renderer.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

namespace engine = ::pooppop::sdl_game_engine;

engine::Renderer* engine::Renderer::instance = nullptr;

engine::Renderer* engine::Renderer::GetInstance() {
	if (instance == nullptr) {
		instance = new Renderer();
	}

	return instance;
}

bool engine::Renderer::Init(std::string applicationName, int screenWidth,
	int screenHeight)
{
	int imgFlags;
	int a;

	SetBackground(0x00, 0x00, 0x00);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
			<< std::endl;
		return false;
	}

	gWindow = SDL_CreateWindow(applicationName.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (gWindow == NULL)
	{
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
			<< std::endl;
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (gRenderer == NULL)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError()
			<< std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// start image loader
	imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: "
			<< IMG_GetError() << std::endl;
		return false;
	}

	// start font loader
	/*if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "
			<< TTF_GetError() << std::endl;
		return false;
	}*/
	/*
	// start audio loader
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error : "
			<< Mix_GetError() << endl;
		return false;
	}*/

	return true;
}

void engine::Renderer::SetBackground(int red, int green, int blue)
{
	cBackground[0] = red;
	cBackground[1] = green;
	cBackground[2] = blue;
}

void engine::Renderer::Close()
{
	imageCache.Close();
	//fontCashe.close();
	//soundCashe.close();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Mix_Quit();
	//TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void engine::Renderer::Clear()
{
	// print all window with the background color
	SDL_SetRenderDrawColor(gRenderer, cBackground[0], cBackground[1],
		cBackground[2], 0xFF);
	SDL_RenderClear(gRenderer);
}

void engine::Renderer::DrawFinalize()
{
	SDL_RenderPresent(gRenderer);
}

engine::Texture* engine::Renderer::RequestTexture(std::string filename)
{
	Texture* newTexture = NULL;
	SDL_Surface* myImage = NULL;

	// loading is dealt with in SDLImageCache
	myImage = imageCache.LoadImage(filename);

	if (myImage == NULL)
	{
		std::cout << "Could not load image with filename " << filename.c_str()
			<< std::endl;
		return NULL;
	}

	newTexture = new Texture(myImage, gRenderer);

	if (newTexture == NULL)
	{
		std::cout << "Could not create texture with filename " << filename.c_str()
			<< std::endl;
		return NULL;
	}

	return newTexture;
}

void engine::Renderer::DrawRect(float x, float y, float width, float height,
	int red, int green, int blue, int alpha, bool fill)
{
	SDL_Rect rect = { x, y, width, height };

	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, red, green, blue, alpha);

	if (fill)
	{
		SDL_RenderFillRect(gRenderer, &rect);
	}
	else
	{
		SDL_RenderDrawRect(gRenderer, &rect);
	}
}

int engine::Renderer::GetWindowHeight()
{
	int height;

	SDL_GetWindowSize(gWindow, NULL, &height);

	return height;
}

int engine::Renderer::GetWindowWidth()
{
	int width;

	SDL_GetWindowSize(gWindow, &width, NULL);

	return width;
}

/*engine::Texture* engine::Renderer::RequestFontTexture(std::string text,
	std::string fontFilename, int size, int red, int green, int blue, float* width, float* height)
{
	Texture* newTexture = NULL;
	TTF_Font* myFont = NULL;
	SDL_Color textColor = { red, green, blue };
	SDL_Surface* mySurface = NULL;

	// loading is dealt with in SDLFontCache
	myFont = fontCashe.loadFont(fontFilename, size);

	if (myFont == NULL)
	{
		std::cout << "Could not load font with filename " << fontFilename.c_str()
			<< std::endl;
		return NULL;
	}

	// returns a surface (what we call texture)
	mySurface = TTF_RenderText_Solid(myFont, text.c_str(), textColor);

	if (mySurface == NULL)
	{
		std::cout << "Could not create texture with font with filename "
			<< fontFilename.c_str() << std::endl;
		return NULL;
	}

	*width = mySurface->w;
	*height = mySurface->h;

	newTexture = new Texture(mySurface, gRenderer);

	if (newTexture == NULL)
	{
		std::cout << "Could not create text texture with font "
			<< fontFilename.c_str() << std::endl;
		return NULL;
	}

	return newTexture;
}*/
