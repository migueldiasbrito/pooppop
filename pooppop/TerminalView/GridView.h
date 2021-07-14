#ifndef POOPPOP_TERMINALVIEW_GRIDVIEW_H_
#define POOPPOP_TERMINALVIEW_GRIDVIEW_H_

#include "../Controller/GridController.h"

namespace controller = ::pooppop::controller;

namespace pooppop {
	namespace terminalview {
		class GridView
		{
		public:
			GridView(controller::GridController*);
			void DisplayView();
		private:
			controller::GridController* gridController;
		};
	}
}

#endif  // POOPPOP_TERMINALVIEW_GRIDVIEW_H_
