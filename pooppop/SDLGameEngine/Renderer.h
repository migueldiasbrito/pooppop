#ifndef POOPPOP_SDLGAMEENGINE_RENDERER_H_
#define POOPPOP_SDLGAMEENGINE_RENDERER_H_

#include <string>
#include "Texture.h"
#include <list>
#include "ImageCache.h"

namespace pooppop {
	namespace sdl_game_engine {
		class Renderer
		{
		public:
			static Renderer* GetInstance();

			//! Starts the graphics engine
			/*!
			\param applicationName application name (e.g. window name).
			\param screenWidth screen width.
			\param screenHeight screen height.
			\return true if the engine started
			*/
			bool Init(std::string applicationName, int screenWidth,
				int screenHeight);

			//! Sets the background color displayed
			/*!
			Default should be black. If an image was previously provided, it should be
			deleted
			\param red red component (0-255)
			\param green green component (0-255)
			\param blue blue component (0-255)
			*/
			void SetBackground(int red, int green, int blue);

			//! Terminates the engine
			void Close();

			//! Everything drawn is erased from the screen
			void Clear();

			//! Ends the new frame proccess
			void DrawFinalize();

			//! Requests a texture usable by the graphics engine
			/*!
			\param filename texture name.
			\return the loaded texture if it exists
			*/

			Texture* RequestTexture(std::string filename);

			//! Draws a rect on the screen
			/*!
			\param x x coordinate of the rect top left corner
			\param y y coordinate of the rect top left corner
			\param width rect width
			\param height rect height
			\param red rect color red component (0-255)
			\param green rect color green component (0-255)
			\param blue rect color blue component (0-255)
			\param alpha rect color alpha component (0-255)
			\param fill if false, draws only the contour
			*/
			void DrawRect(float x, float y, float width, float height, int red,
				int green, int blue, int alpha, bool fill);

			//! Returns the window width
			/*!
			\return window width
			*/
			int GetWindowWidth();

			//! Returns the window height
			/*!
			\return window height
			*/
			int GetWindowHeight();

			//! Requests a text only texture
			/*!
			\param text the text that should appear on the texture.
			\param fontFilename filename of the text font.
			\param size text size
			\param red text color red component (0-255)
			\param green text color green component (0-255)
			\param blue text color blue component (0-255)
			\param width the loaded texture width
			\param height the loaded texture height
			\return The test results
			\sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
			*/
			//Texture* RequestFontTexture(std::string text, std::string fontFilename,
			//	int size, int red, int green, int blue, float* width, float* height);
		private:
			static Renderer* instance;

			//! SDL Window.
			/*!
			The window is created on init method and destroyed on close
			*/
			SDL_Window* gWindow = NULL;

			//! SDL Renderer.
			/*!
			The renderer is reponsible for all drawing operations. Like the SDL
			window, is created on init and destroyed on close
			*/
			SDL_Renderer* gRenderer = NULL;

			//! Image cache.
			/*!
			Saves any image on memory so that it can be used again without loading.
			*/
			ImageCache imageCache;

			//! Font cache.
			/*!
			Saves any font on memory so that it can be used again without loading.
			*/
			//FontCache fontCache;

			//! Sound cache.
			/*!
			Saves any Sound clips on memory so that it can be used again without
			loading.
			*/
			//SoundCache soundCache;

			//! Background color
			/*!
			Current background color (red, green, blue)
			*/
			int cBackground[3];

			//! Current events.
			/*!
			Clear and filled everytime updateEvents is called and used on every
			IInputProvider method implementation
			*/
			std::list<SDL_Event> currentEvents;

			inline Renderer() {}
		};
	}
}

#endif  // POOPPOP_SDLGAMEENGINE_RENDERER_H_