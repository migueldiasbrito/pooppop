#include "Grid.h"

namespace model = ::pooppop::model;

model::Grid::Grid(int rows, int columns) : grid(rows, std::vector<Piece*>(columns, nullptr)) {
	this->rows = rows;
	this->columns = columns;
}

model::Piece* model::Grid::GetPieceAt(int row, int column) {
	if (row < 0 || row >= this->rows || column < 0 || column >= this->columns) {
		return nullptr;
	}

	return this->grid[row][column];
}

bool model::Grid::SetPieceAt(model::Piece* piece, int row, int column) {
	if (row < 0 || row >= this->rows || column < 0 || column >= this->columns || GetPieceAt(row, column) != nullptr) {
		return false;
	}

	this->grid[row][column] = piece;

	return true;
}