// pooppop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Model/Pair.h"
#include "Model/Piece.h"
#include "Controller/GridController.h"
#include "TerminalView/GridView.h"
#include "Fsm/StateMachine.h"

namespace model = ::pooppop::model;
namespace controller = ::pooppop::controller;
namespace view = ::pooppop::terminalview;
controller::GridController* gridController = nullptr;
view::GridView* gridView = nullptr;

void onLoad() {
    gridController = new controller::GridController(8, 16);
    gridView = new view::GridView(gridController);
}

void onDraw() {
    gridView->DisplayView();
}

void onPlay() {
    model::Piece a(0), b(1);
    model::Pair abup(&a, &b, model::Pair::Orientation::VERTICAL);

    while (gridController->AddPair(&abup, 8)) {

    }
}

int main()
{
    namespace fsm = ::pooppop::fsm;
    fsm::StateMachine stateMachine;

    stateMachine.AddState("loading");
    stateMachine.AddState("draw");
    stateMachine.AddState("play");

    stateMachine.AddTransition("load", { "none" }, "loading");
    stateMachine.AddTransition("drawGrid", { "loading", "play" }, "draw");
    stateMachine.AddTransition("startPlay", { "draw" }, "play");

    fsm::State* state = stateMachine.GetState("loading");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onLoad);
    }

    state = stateMachine.GetState("draw");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onDraw);
    }

    state = stateMachine.GetState("play");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onPlay);
    }

    stateMachine.TriggerTransition("load");
    stateMachine.TriggerTransition("drawGrid");
    stateMachine.TriggerTransition("startPlay");
    stateMachine.TriggerTransition("drawGrid");

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
