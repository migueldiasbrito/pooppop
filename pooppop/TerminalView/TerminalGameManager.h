#ifndef POOPPOP_TERMINALVIEW_TERMINALGAMEMANAGER_H_
#define POOPPOP_TERMINALVIEW_TERMINALGAMEMANAGER_H_

#include "../Game/IGameManager.h"
#include "../Fsm/StateMachine.h"
#include "../Controller/GridController.h"
#include "GridView.h"

namespace game = ::pooppop::game;
namespace fsm = ::pooppop::fsm;
namespace controller = ::pooppop::controller;

namespace pooppop {
	namespace terminalview {
		class TerminalGameManager : public game::IGameManager
		{
		public:
			TerminalGameManager();
			int Play();
			void OnLoad();
			void OnEnd();
			inline fsm::StateMachine* GetStateMachine() { return &stateMachine; }

		private:
			fsm::StateMachine stateMachine;
			controller::GridController* gridController = nullptr;
			GridView* gridView = nullptr;
			bool gameOver = false;
		};
	}
}

#endif  // POOPPOP_TERMINALVIEW_TERMINALGAMEMANAGER_H_
