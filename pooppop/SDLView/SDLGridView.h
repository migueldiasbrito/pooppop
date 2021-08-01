#ifndef POOPPOP_SDLVIEW_SDLGRIDVIEW_H_
#define POOPPOP_SDLVIEW_SDLGRIDVIEW_H_

#include "../Controller/GridController.h"

namespace controller = ::pooppop::controller;

namespace pooppop {
	namespace sdlview {
		class SDLGridView
		{
		public:
			SDLGridView(controller::GridController*);
			void DisplayView();
		private:
			controller::GridController* gridController;
		};
	}
}

#endif  // POOPPOP_SDLVIEW_SDLGRIDVIEW_H_