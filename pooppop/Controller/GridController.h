#ifndef POOPPOP_CONTROLLER_GRIDCONTROLLER_H_
#define POOPPOP_CONTROLLER_GRIDCONTROLLER_H_

#include "../Model/Grid.h"
#include <list>

namespace model = ::pooppop::model;

namespace pooppop {
	namespace controller {
		class GridController
		{
		public:
			GridController(int, int);
			bool AddPair(model::Pair*, int);
			inline model::Grid* GetGrid() { return &grid; }
			void DetectShapes();
		private:
			struct Shape
			{
				std::list<std::pair<int, int>> pieces;
			};

			model::Grid grid;
			std::list<std::pair<int, int>> uncheckedPieces;

			bool DropPiece(model::Piece*, int);
			int LastEmptyRow(int);
			Shape getShape(int, int);
			void AddUniqueIfSameColor(int, int, int, std::list<std::pair<int, int>>*);
			void DeleteShapes(std::vector<Shape>*);
			void DeletePieceAndUpdateColumn(int, int);
			void UpdateRemainingShapesPieces(std::vector<Shape>*, int, std::list<std::pair<int, int>>::iterator);
			void AddUncheckedPiece(int, int);
			void RemoveUncheckedPiece(int, int);
			void AddUpdateUncheckedPiece(int, int, int, int);
		};
	}
}

#endif  // POOPPOP_CONTROLLER_GRIDCONTROLLER_H_