#ifndef POOPPOP_SDLGAMEENGINE_GAMEOBJECT_H_
#define POOPPOP_SDLGAMEENGINE_GAMEOBJECT_H_

#include <string>
#include "Texture.h"

namespace pooppop {
	namespace sdl_game_engine {

		//!  Any Game Object
		/*!
		A Game Object is something that appears on the screen, for example: a
		button, a character, a score display.
		*/

		class GameObject
		{
		public:
			//! Constructor with texture
			/*!
			\param x top left corner coordinate x
			\param y top left corner coordinate y
			\param width object width
			\param height object height
			\param textureFilename object texture filename
			*/
			GameObject(float x, float y, float width, float height,
				std::string textureFilename);

			//! Constructor with color (rect)
			/*!
			\param x top left corner coordinate x
			\param y top left corner coordinate y
			\param width object width
			\param height object height
			\param red rbga color red component
			\param green rbga color green component
			\param blue rbga color blue component
			\param alpha rbga color alpha component
			*/
			GameObject(float x, float y, float width, float height, int red, int green,
				int blue, int alpha);

			//! Constructor with text
			/*!
			\param x top left corner coordinate x
			\param y top left corner coordinate y
			\param width object width
			\param height object height
			\param fontFilename text font filename
			\param size font size
			\param text the text to display
			\param red rbg color red component
			\param green rbg color green component
			\param blue rbg color blue component
			*/
			/*GameObject(float x, float y, std::string fontFilename, int size,
				std::string text, int red, int green, int blue);*/

			//! Destructor
			~GameObject();

			//! Draws the object
			virtual void Draw();

			//! Updates the object
			/*!
			\param elapsedTime elapsed time since the last update
			\returns false if it should be destroyed
			*/
			virtual bool Update(float elapsedTime);

			//! X Getter
			/*!
			\returns top left x coordinate
			*/
			virtual float GetX();

			//! Y Getter
			/*!
			\returns top left y coordinate
			*/
			virtual float GetY();

			//! Width Getter
			/*!
			\returns object width
			*/
			virtual float GetWidth();

			//! Height Getter
			/*!
			\returns object height
			*/
			virtual float GetHeight();

			//! Texture Setter
			/*!
			\param newTexture the new texture
			\param shared whether the texture can be shared by other objects
			\param deleteCurr delete object current texture
			*/
			virtual void SetTexture(Texture* newTexture, bool shared = false,
				bool deleteCurr = false);

		protected:
			//! Top left corner x
			float x;

			//! Top left corner y
			float y;

			//! Object width
			float width;

			//! Object height
			float height;

			//! Object rgba color red component
			int red;

			//! Object rgba color green component
			int green;

			//! Object rgba color blue component
			int blue;

			//! Object rgba color alpha component
			int alpha;

			//! Object texture
			Texture* myTexture;

			//! Whether the texture is unique for this object
			bool textShared;
		};
	}
}

#endif  // POOPPOP_SDLGAMEENGINE_GAMEOBJECT_H_
