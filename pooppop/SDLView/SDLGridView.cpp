#include "SDLGridView.h"
#include "../Game/IGameManager.h"
#include "../SDLGameEngine/Renderer.h"
#include <Windows.h>

namespace view = ::pooppop::sdlview;
namespace game = ::pooppop::game;
namespace engine = ::pooppop::sdl_game_engine;

view::SDLGridView::SDLGridView(controller::GridController* gridController) {
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

void view::SDLGridView::DisplayView() {
	engine::Renderer* renderer = engine::Renderer::GetInstance();
	renderer->Clear();

	model::Grid* grid = gridController->GetGrid();
	float x, y;
	int red, green, blue;
	for (int row = grid->GetRows() - 1; row >= 0; row--) {
		for (int column = 0; column < grid->GetColumns(); column++) {
			model::Piece* piece = grid->GetPieceAt(row, column);
			if (piece != nullptr) {
				x = 200 + column * 30;
				y = 450 - row * 30;

				switch (piece->GetColor())
				{
				case 0:
					red = 255;
					green = 0;
					blue = 0;
					break;
				case 1:
					red = 0;
					green = 255;
					blue = 0;
					break;
				case 2:
					red = 0;
					green = 0;
					blue = 255;
					break;
				case 3:
					red = 255;
					green = 0;
					blue = 255;
					break;
				default:
					red = 0;
					green = 0;
					blue = 0;
					break;
				}

				renderer->DrawRect(x, y, 30, 30, red, green, blue, 255, true);
			}
		}
	}

	renderer->DrawFinalize();

	Sleep(1000);
}
