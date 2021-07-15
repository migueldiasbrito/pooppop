#ifndef POOPPOP_FSM_STATEMACHINE_H_
#define POOPPOP_FSM_STATEMACHINE_H_

#include <string>
#include <vector>
#include <map>
#include "State.h"

namespace pooppop {
	namespace fsm {
		class StateMachine
		{
		public:
			inline StateMachine() { currentState = "none"; AddState("none"); }
			void AddState(std::string);
			void AddTransition(std::string, std::vector<std::string>, std::string);
			State* GetState(std::string);
			void TriggerTransition(std::string);

		private:
			struct Transition
			{
				std::vector<std::string> from;
				std::string to;
			};

			std::map<std::string, State> states;
			std::map<std::string, Transition> transitions;
			std::string currentState;
		};
	}
}

#endif  // POOPPOP_FSM_STATEMACHINE_H_
