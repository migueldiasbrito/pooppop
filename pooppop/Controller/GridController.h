#ifndef POOPPOP_CONTROLLER_GRIDCONTROLLER_H_
#define POOPPOP_CONTROLLER_GRIDCONTROLLER_H_

#include "../Model/Grid.h"

namespace model = ::pooppop::model;

namespace pooppop {
	namespace controller {
		class GridController
		{
		public:
			GridController(int, int);
			bool AddPair(model::Pair*, int);
			inline model::Grid* GetGrid() { return &grid; }
		private:
			model::Grid grid;

			bool DropPiece(model::Piece*, int);
			int LastEmptyRow(int);
		};
	}
}

#endif  // POOPPOP_CONTROLLER_GRIDCONTROLLER_H_