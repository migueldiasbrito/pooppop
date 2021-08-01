#ifndef POOPPOP_SDLGAMEENGINE_TEXTURE_H_
#define POOPPOP_SDLGAMEENGINE_TEXTURE_H_

#include "SDL.h"

namespace pooppop {
	namespace sdl_game_engine {

		//!  Helper class to deal with SDL textures

		class Texture
		{
		public:
			Texture(SDL_Surface* image, SDL_Renderer* gRenderer);
			~Texture();

			//! Closes the texture
			void Close();

			//! Draws the texture
			/*!
			\param x top left x coordinate where the texture should be drawn
			\param y top left y coordinate where the texture should be drawn
			\param w width of the drawn texture
			\param h height of the drawn texture
			*/
			void DrawAt(int x, int y, int w, int h);

			//! Sets the blend mode
			/*!
			\param blending true for blend mode
			*/
			void SetBlendMode(bool blending);

			//! Changes texture color
			/*!
			\param red red component (0-255)
			\param green green component (0-255)
			\param blue blue component (0-255)
			*/
			void ManipulateColors(float red, float blue, float green);

			//! Changes texture tranparency
			/*!
			\param alpha rgba alpha component (0-255)
			*/
			void ManipulateAlpha(float alpha);
		private:
			//! SDL Texture.
			SDL_Texture* myTexture = NULL;

			//! SDL Context.
			/*!
			To create a SDL Texture, it needs the rederer that it will be used on.
			*/
			SDL_Renderer* context = NULL;
		};
	}
}

#endif  // POOPPOP_SDLGAMEENGINE_TEXTURE_H_
