#include "StateMachine.h"
#include <stdexcept>

namespace fsm = ::pooppop::fsm;

void fsm::StateMachine::AddState(std::string state) {
	states.insert(std::pair<std::string, State>(state, State()));
}

void fsm::StateMachine::AddTransition(std::string transition, std::vector<std::string> from, std::string to) {
	transitions.insert(std::pair<std::string, Transition>(transition, { from, to } ));
}

fsm::State* fsm::StateMachine::GetState(std::string state) {
	try {
		return &(states.at(state));
	}
	catch (const std::out_of_range& e) {
		return nullptr;
	}
}

void fsm::StateMachine::TriggerTransition(std::string transition) {
	Transition t;
	try {
		t = transitions.at(transition);
	}
	catch (const std::out_of_range& e) {
		return;
	}

	if (std::find(t.from.begin(), t.from.end(), currentState) == t.from.end()) { return; }

	State* state = GetState(t.to);
	if (state == nullptr) { return; }

	currentState = t.to;
	state->Enter();
}


void fsm::StateMachine::QueueTransition(std::string transition) {
	transitionsQueue.push(transition);
}

void fsm::StateMachine::Update() {
	if (!transitionsQueue.empty()) {
		TriggerTransition(transitionsQueue.front());
		transitionsQueue.pop();
	}
}