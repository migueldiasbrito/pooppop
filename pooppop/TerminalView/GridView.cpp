#include "GridView.h"
#include <iostream>

namespace view = ::pooppop::terminalview;

view::GridView::GridView(controller::GridController* gridController) {
	this->gridController = gridController;
}

void view::GridView::DisplayView() {
	model::Grid* grid = gridController->GetGrid();
	std::cout << std::endl << "GRID" << std::endl << std::endl;

	for (int row = grid->GetRows() - 1; row >= 0; row--) {
		for (int column = 0; column < grid->GetColumns(); column++) {
			model::Piece* piece = grid->GetPieceAt(row, column);
			if (piece == nullptr) {
				std::cout << "- ";
			}
			else {
				std::cout << piece->GetColor() << " ";
			}
		}
		std::cout << std::endl;
	}
}