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

void model::Grid::DeletePiece(int row, int column) {
	if (row < 0 || row >= this->rows || column < 0 || column >= this->columns || GetPieceAt(row, column) == nullptr) {
		return;
	}

	delete this->grid[row][column];
	this->grid[row][column] = nullptr;
}

void model::Grid::ExchangePieces(int row1, int column1, int row2, int column2) {
	if (row1 < 0 || row1 >= this->rows || column1 < 0 || column1 >= this->columns ||
		row2 < 0 || row2 >= this->rows || column2 < 0 || column2 >= this->columns) {
		return;
	}

	Piece* piece1 = GetPieceAt(row1, column1), * piece2 = GetPieceAt(row2, column2);

	this->grid[row1][column1] = piece2;
	this->grid[row2][column2] = piece1;
}
