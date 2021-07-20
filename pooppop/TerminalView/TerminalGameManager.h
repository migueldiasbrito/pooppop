#ifndef POOPPOP_TERMINALVIEW_TERMINALGAMEMANAGER_H_
#define POOPPOP_TERMINALVIEW_TERMINALGAMEMANAGER_H_

#include "../Fsm/StateMachine.h"
#include "../Controller/GridController.h"
#include "GridView.h"

namespace fsm = ::pooppop::fsm;
namespace controller = ::pooppop::controller;

namespace pooppop {
	namespace terminalview {
		class TerminalGameManager
		{
		public:
			static TerminalGameManager* GetInstance();

			int Play();
			void OnLoad();
			void OnEnd();
			inline fsm::StateMachine* GetStateMachine() { return &stateMachine; }

		private:
			static TerminalGameManager* instance;

			fsm::StateMachine stateMachine;
			controller::GridController* gridController = nullptr;
			GridView* gridView = nullptr;
			bool gameOver = false;

			TerminalGameManager();
		};
	}
}

#endif  // POOPPOP_TERMINALVIEW_TERMINALGAMEMANAGER_H_
