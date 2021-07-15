#ifndef POOPPOP_FSM_STATE_H_
#define POOPPOP_FSM_STATE_H_

#include <list>
#include <functional>

namespace pooppop {
	namespace fsm {
		class State
		{
		public:
			typedef std::list<std::function<void()>>::iterator callback_id;

			inline State() {}
			callback_id RegisterOnEnterCallback(std::function<void()>);
			void UnregisterOnEnterCallback(callback_id);
			void Enter();

		private:
			std::list<std::function<void()>> onEnterCallbacks;
		};
	}
}

#endif  // POOPPOP_FSM_STATE_H_
