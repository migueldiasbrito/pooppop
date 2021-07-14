#ifndef POOPPOP_MODEL_GRID_H_
#define POOPPOP_MODEL_GRID_H_

#include "Piece.h"
#include "Pair.h"
#include <vector>

namespace pooppop {
	namespace model {
		class Grid
		{
		public:
			Grid(int, int);
			inline int GetRows() { return rows; }
			inline int GetColumns() { return columns; }
			Piece* GetPieceAt(int, int);
			bool SetPieceAt(Piece*, int, int);
		private:
			std::vector<std::vector<Piece*>> grid;
			int rows;
			int columns;
		};
	}
}

#endif  // POOPPOP_MODEL_GRID_H_