#include "GridView.h"
#include "../Game/IGameManager.h"
#include <iostream>

namespace view = ::pooppop::terminalview;
namespace game = ::pooppop::game;

view::GridView::GridView(controller::GridController* gridController) {
	this->gridController = gridController;

	fsm::StateMachine* stateMachine = game::IGameManager::GetInstance()->GetStateMachine();

	fsm::State* state = stateMachine->GetState("draw");
	if (state != nullptr) {
		state->RegisterOnEnterCallback([this]() -> void {this->DisplayView(); });
	}

	state = stateMachine->GetState("end");
	if (state != nullptr) {
		state->RegisterOnEnterCallback([this]() -> void {this->DisplayView(); });
	}
}

void view::GridView::DisplayView() {
	system("cls");

	model::Grid* grid = gridController->GetGrid();
	std::cout << std::endl << "GRID" << std::endl << std::endl;

	for (int row = grid->GetRows() - 1; row >= 0; row--) {
		for (int column = 0; column < grid->GetColumns(); column++) {
			model::Piece* piece = grid->GetPieceAt(row, column);
			if (piece != nullptr) {
				std::cout << "- ";
			}
			else {
				std::cout << piece->GetColor() << " ";
			}
		}
		std::cout << std::endl;
	}

	std::cin.ignore();
}