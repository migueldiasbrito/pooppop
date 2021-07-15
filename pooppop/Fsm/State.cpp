#include "State.h"

namespace fsm = ::pooppop::fsm;

fsm::State::callback_id fsm::State::RegisterOnEnterCallback(std::function<void()> f) {
	return onEnterCallbacks.insert(onEnterCallbacks.end(), f);
}

void fsm::State::UnregisterOnEnterCallback(fsm::State::callback_id id) {
	onEnterCallbacks.erase(id);
}

void fsm::State::Enter() {
	for (callback_id callback = onEnterCallbacks.begin(); callback != onEnterCallbacks.end(); callback++) {
		(*callback)();
	}
}
