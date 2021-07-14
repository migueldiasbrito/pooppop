#include "GridController.h"

namespace controller = ::pooppop::controller;

controller::GridController::GridController(int rows, int columns) : grid(rows, columns) {

}

bool controller::GridController::AddPair(model::Pair* pair, int column) {
	if (DropPiece(pair->GetFirst(), column)) {
		column += pair->GetOrientation() == model::Pair::Orientation::HORIZONTAL ? 1 : 0;

		return DropPiece(pair->GetSecond(), column);
	}

	return false;
}

bool controller::GridController::DropPiece(model::Piece* piece, int column) {
	int row = LastEmptyRow(column);

	if (row >= grid.GetRows()) { return false; }

	grid.SetPieceAt(piece, row, column);
}

int controller::GridController::LastEmptyRow(int column) {
	if (column < 0 || column >= grid.GetColumns()) {
		return grid.GetRows();
	}

	for (int i = 0; i < grid.GetRows(); i++) {
		if (grid.GetPieceAt(i, column) == nullptr) {
			return i;
		}
	}

	return grid.GetColumns();
}
