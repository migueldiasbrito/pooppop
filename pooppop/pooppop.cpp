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

namespace fsm = ::pooppop::fsm;
fsm::StateMachine stateMachine;

void onLoad() {
    gridController = new controller::GridController(16, 8);
    gridView = new view::GridView(gridController);
}

void onDraw() {
    system("cls");
    gridView->DisplayView();
    std::cin.ignore();
}

void onWaitPlay() {
    model::Piece *a = new model::Piece(rand() % 4), *b = new model::Piece(rand() % 4);
    model::Pair abup(a, b, model::Pair::Orientation(rand() % 2));

    stateMachine.QueueTransition("drawGrid");

    if (gridController->AddPair(&abup, rand() % 7)) {
        stateMachine.QueueTransition("processPlay");
    }
    else {
        stateMachine.QueueTransition("gameOver");
    }
}

void onProcessingPlay() {
    gridController->DetectShapes();
    stateMachine.QueueTransition("drawGrid");
    stateMachine.QueueTransition("play");
}

bool gameOver = false;
void onEnd() {
    
    gridView->DisplayView();
    gameOver = true;
}

int main()
{
    //srand(time(NULL));

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
        state->RegisterOnEnterCallback(onLoad);
    }

    state = stateMachine.GetState("draw");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onDraw);
    }

    state = stateMachine.GetState("waitPlay");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onWaitPlay);
    }

    state = stateMachine.GetState("processingPlay");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onProcessingPlay);
    }

    state = stateMachine.GetState("end");
    if (state != nullptr) {
        state->RegisterOnEnterCallback(onEnd);
    }

    stateMachine.QueueTransition("load");
    stateMachine.QueueTransition("drawGrid");
    stateMachine.QueueTransition("play");

    while (!gameOver) {
        stateMachine.Update();
    }

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
