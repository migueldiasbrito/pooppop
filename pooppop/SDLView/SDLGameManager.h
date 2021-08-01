#ifndef POOPPOP_SDLVIEW_SDLGAMEMANAGER_H_
#define POOPPOP_SDLVIEW_SDLGAMEMANAGER_H_

#include "../Game/IGameManager.h"
#include "../Fsm/StateMachine.h"
#include "../Controller/GridController.h"
#include "SDLGridView.h"
#include <SDL.h>

namespace game = ::pooppop::game;
namespace fsm = ::pooppop::fsm;
namespace controller = ::pooppop::controller;

namespace pooppop {
	namespace sdlview {
		class SDLGameManager : public game::IGameManager
		{
		public:
			SDLGameManager();
			~SDLGameManager();
			int Play();
			void OnLoad();
			void OnEnd();
			inline fsm::StateMachine* GetStateMachine() { return &stateMachine; }

		private:
			fsm::StateMachine stateMachine;
			controller::GridController* gridController = nullptr;
			bool gameOver = false;
			SDLGridView* gridView = nullptr;
		};
	}
}

#endif  // POOPPOP_SDLVIEW_SDLGAMEMANAGER_H_