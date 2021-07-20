#include "GridController.h"
#include "../Fsm/StateMachine.h"
#include "../TerminalView/TerminalGameManager.h"
#include <iostream>

namespace controller = ::pooppop::controller;
namespace fsm = ::pooppop::fsm;
namespace view = ::pooppop::terminalview;

controller::GridController::GridController(int rows, int columns) : grid(rows, columns) {
	fsm::StateMachine* stateMachine = terminalview::TerminalGameManager::GetInstance()->GetStateMachine();

	fsm::State* state = stateMachine->GetState("waitPlay");
	if (state != nullptr) {
		state->RegisterOnEnterCallback([this]() -> void {this->StartNewPlay(); });
	}

	state = stateMachine->GetState("processingPlay");
	if (state != nullptr) {
		state->RegisterOnEnterCallback([this, stateMachine]() -> void {
			this->DetectShapes();
			stateMachine->QueueTransition("drawGrid");
			stateMachine->QueueTransition("play");
		});
	}
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

	while (uncheckedPieces.size() > 0) {
		shapes.clear();
		std::list<std::pair<int, int>>::iterator it = uncheckedPieces.begin();
		for (; it != uncheckedPieces.end(); it++) {
			Shape shape = getShape(it->first, it->second);
			if (shape.pieces.size() > 3) {
				shapes.push_back(shape);
			}
		}
		uncheckedPieces.clear();

		DeleteShapes(&shapes);
	}
}

void controller::GridController::StartNewPlay() {
	model::Piece* a = new model::Piece(rand() % 4), * b = new model::Piece(rand() % 4);
	model::Pair abup(a, b, model::Pair::Orientation(rand() % 2));

	fsm::StateMachine* stateMachine = terminalview::TerminalGameManager::GetInstance()->GetStateMachine();

	stateMachine->QueueTransition("drawGrid");

	if (AddPair(&abup, rand() % 7)) {
		stateMachine->QueueTransition("processPlay");
	}
	else {
		stateMachine->QueueTransition("gameOver");
	}
}

bool controller::GridController::DropPiece(model::Piece* piece, int column) {
	int row = LastEmptyRow(column);

	if (row >= grid.GetRows()) { return false; }

	grid.SetPieceAt(piece, row, column);

	AddUncheckedPiece(row, column);

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

	return grid.GetRows();
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

		RemoveUncheckedPiece(row, column);
	}
}

void controller::GridController::DeleteShapes(std::vector<Shape> *shapes) {
	for (int i = 0; i < shapes->size(); i++) {
		std::list<std::pair<int, int>>::iterator it = shapes->at(i).pieces.begin();
		for (; it != shapes->at(i).pieces.end(); it++) {
			int row = it->first;
			int column = it->second;

			DeletePieceAndUpdateColumn(row, column);
			UpdateRemainingShapesPieces(shapes, i, it);
		}
	}
}

void controller::GridController::DeletePieceAndUpdateColumn(int row, int column) {
	model::Piece* piece = grid.GetPieceAt(row, column);

	if (piece == nullptr) { return; }

	grid.DeletePiece(row, column);
	RemoveUncheckedPiece(row, column);

	for (row++; row < grid.GetRows(); row++) {
		if (grid.GetPieceAt(row, column) == nullptr) { break; }

		grid.ExchangePieces(row - 1, column, row, column);

		AddUpdateUncheckedPiece(row, column, row - 1, column);
	}
}

void controller::GridController::UpdateRemainingShapesPieces(std::vector<Shape>* shapes, int currentShape, std::list<std::pair<int, int>>::iterator currentPiece) {
	int row = currentPiece->first;
	int column = currentPiece->second;

	for (int i = currentShape; i < shapes->size(); i++) {
		std::list<std::pair<int, int>>::iterator it = (i == currentShape) ? std::next(currentPiece, 1) : shapes->at(i).pieces.begin();
		for (; it != shapes->at(i).pieces.end(); it++) {
			if (it->second != column || it->first <= row) { continue; }

			it->first--;
		}
	}
}

void controller::GridController::AddUncheckedPiece(int row, int column) {
	std::pair<int, int> pair(row, column);
	std::list<std::pair<int, int>>::iterator it = std::find(uncheckedPieces.begin(), uncheckedPieces.end(), pair);
	if (it == uncheckedPieces.end()) {
		uncheckedPieces.push_back(std::pair<int, int>(row, column));
	}
}

void controller::GridController::AddUpdateUncheckedPiece(int row, int column, int newRow, int newColumn) {
	std::pair<int, int> pair(row, column);
	std::list<std::pair<int, int>>::iterator it = std::find(uncheckedPieces.begin(), uncheckedPieces.end(), pair);
	if (it != uncheckedPieces.end()) {
		it->first = newRow;
		it->second = newColumn;
	}
	else {
		uncheckedPieces.push_back(std::pair<int, int>(newRow, newColumn));
	}
}

void controller::GridController::RemoveUncheckedPiece(int row, int column) {
	std::pair<int, int> pair(row, column);
	std::list<std::pair<int, int>>::iterator it = std::find(uncheckedPieces.begin(), uncheckedPieces.end(), pair);
	if (it != uncheckedPieces.end()) {
		uncheckedPieces.erase(it);
	}
}
