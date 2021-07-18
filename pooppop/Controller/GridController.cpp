#include "GridController.h"
#include <iostream>

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

void controller::GridController::DetectShapes() {
	std::vector<Shape> shapes;
	std::list<std::pair<int, int>>::iterator it = uncheckedPieces.begin();
	for (; it != uncheckedPieces.end(); it++) {
		Shape shape = getShape(it->first, it->second);
		if (shape.pieces.size() > 3) {
			shapes.push_back(shape);
		}
	}

	std::cout << "Shapes" << std::endl;
	for (unsigned int i = 0; i < shapes.size(); i++) {
		std::cout << i;
		it = shapes[i].pieces.begin();
		for (; it != shapes[i].pieces.end(); it++) {
			std::cout << "(" << it->first << "," << it->second << ") ";
		}
		std::cout << std::endl << std::endl;
	}

	uncheckedPieces.clear();
}

bool controller::GridController::DropPiece(model::Piece* piece, int column) {
	int row = LastEmptyRow(column);

	if (row >= grid.GetRows()) { return false; }

	grid.SetPieceAt(piece, row, column);

	uncheckedPieces.push_back(std::pair<int, int>(row, column));

	return true;
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

controller::GridController::Shape controller::GridController::getShape(int row, int column) {
	Shape shape;
	shape.pieces.push_back(std::pair<int, int>(row, column));

	std::list<std::pair<int, int>>::iterator it = shape.pieces.begin();
	for (; it != shape.pieces.end(); it++) {
		int currRow = it->first;
		int currCol = it->second;
		int color = grid.GetPieceAt(currRow, currCol)->GetColor();

		AddUniqueIfSameColor(currRow - 1, currCol, color, &shape.pieces);
		AddUniqueIfSameColor(currRow + 1, currCol, color, &shape.pieces);
		AddUniqueIfSameColor(currRow, currCol - 1, color, &shape.pieces);
		AddUniqueIfSameColor(currRow, currCol + 1, color, &shape.pieces);
	}

	return shape;
}

void controller::GridController::AddUniqueIfSameColor(int row, int column, int color, std::list<std::pair<int, int>>* vector) {
	if (row < 0 || row >= grid.GetRows()) { return; }
	if (column < 0 || column >= grid.GetColumns()) { return; }
	if (grid.GetPieceAt(row, column) == nullptr) { return; }
	if (grid.GetPieceAt(row, column)->GetColor() != color) { return; }

	std::pair<int, int> pair(row, column);
	if (std::find(vector->begin(), vector->end(), pair) == vector->end()) {
		vector->push_back(pair);

		std::list<std::pair<int, int>>::iterator it = std::find(uncheckedPieces.begin(), uncheckedPieces.end(), pair);
		if (it != uncheckedPieces.end()) {
			uncheckedPieces.erase(it);
		}
	}
}
