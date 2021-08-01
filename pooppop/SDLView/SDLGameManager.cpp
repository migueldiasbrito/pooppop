#include "SDLGameManager.h"
#include "../SDLGameEngine/Renderer.h"

namespace view = ::pooppop::sdlview;
namespace engine = ::pooppop::sdl_game_engine;

view::SDLGameManager::SDLGameManager() {
	SetInstance(this);

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

view::SDLGameManager::~SDLGameManager () {
	delete gridController;
	delete gridView;
}

int view::SDLGameManager::Play() {
	while (!gameOver) {
		stateMachine.Update();
	}

	return 0;
}

void view::SDLGameManager::OnLoad() {
	engine::Renderer* renderer = engine::Renderer::GetInstance();

	if (!renderer->Init("PoopPop", 640, 480)) {
		gameOver = true;
		return;
	}
	renderer->SetBackground(0, 0, 0);

	gridController = new controller::GridController(16, 8);
	gridView = new view::SDLGridView(gridController);
}

void view::SDLGameManager::OnEnd() {
	gameOver = true;

	engine::Renderer* renderer = engine::Renderer::GetInstance();
	renderer->Close();
}
