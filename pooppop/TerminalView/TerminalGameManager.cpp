#include "TerminalGameManager.h"

namespace view = ::pooppop::terminalview;

view::TerminalGameManager* view::TerminalGameManager::GetInstance() {
	if (instance == nullptr) {
		instance = new TerminalGameManager();
	}
	return instance;
}

view::TerminalGameManager* view::TerminalGameManager::instance = nullptr;

view::TerminalGameManager::TerminalGameManager() {
	stateMachine.AddState("loading");
	stateMachine.AddState("draw");
	stateMachine.AddState("waitPlay");
	stateMachine.AddState("processingPlay");
	stateMachine.AddState("end");

	stateMachine.AddTransition("load", { "none" }, "loading");
	stateMachine.AddTransition("drawGrid", { "loading", "waitPlay", "processingPlay" }, "draw");
	stateMachine.AddTransition("play", { "draw" }, "waitPlay");
	stateMachine.AddTransition("processPlay", { "draw" }, "processingPlay");
	stateMachine.AddTransition("gameOver", { "draw" }, "end");

	fsm::State* state = stateMachine.GetState("loading");
	if (state != nullptr) {
		state->RegisterOnEnterCallback([this]() -> void {this->OnLoad(); });
	}

	state = stateMachine.GetState("end");
	if (state != nullptr) {
		state->RegisterOnEnterCallback([this]() -> void {this->OnEnd(); });
	}

	stateMachine.QueueTransition("load");
	stateMachine.QueueTransition("drawGrid");
	stateMachine.QueueTransition("play");
}

int view::TerminalGameManager::Play() {
	while (!gameOver) {
		stateMachine.Update();
	}

	return 0;
}

void view::TerminalGameManager::OnLoad() {
	gridController = new controller::GridController(16, 8);
	gridView = new view::GridView(gridController);
}

void view::TerminalGameManager::OnEnd() {
	gameOver = true;
}
