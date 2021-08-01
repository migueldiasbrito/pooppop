#ifndef POOPPOP_SDLGAMEENGINE_SCENE_H_
#define POOPPOP_SDLGAMEENGINE_SCENE_H_

#include <vector>
#include "GameObject.h"

namespace pooppop {
	namespace sdl_game_engine {
		class Scene
		{
		public:
			//! Starts the game
			/*!
			\return true if successful
			*/
			virtual bool Open();

			//! Updates the game
			/*!
			\return true if it should continue to update
			*/
			virtual bool Loop();

			//! Closes the game, delelting all Game Objects
			virtual void Close();

		protected:
			//! Expected Frame Rate
			/// \todo calcule real frame rate
			const int FRAME_RATE = 60;

			//! Array with all Game Objects.
			std::vector<GameObject*> gameObjects;

			//! Updates all Game Objects
			virtual void Update();

			//! Draws all Game Objects
			virtual void Draw();

			//! Handles input
			virtual void HandleInput();
		};
	}
}

#endif  // POOPPOP_SDLGAMEENGINE_SCENE_H_
