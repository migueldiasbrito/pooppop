#ifndef POOPPOP_SDLGAMEENGINE_IMAGECACHE_H_
#define POOPPOP_SDLGAMEENGINE_IMAGECACHE_H_

#include "SDL_image.h"
#include <map>
#include <string>

namespace pooppop {
	namespace sdl_game_engine {
		class ImageCache
		{
		public:
			//! Loads or retrieves image from file
			/*!
			\param filename image filename.
			\return loaded image in a SDL container
			*/
			SDL_Surface* LoadImage(std::string filename);

			//! Unloads all the images
			void Close();

		private:
			//! Cache.
			/*!
			For every image loaded, it is inserted in this map with its filename.
			*/
			std::map<std::string, SDL_Surface*> imageCache;
		};
	}
}

#endif  // POOPPOP_SDLGAMEENGINE_IMAGECACHE_H_