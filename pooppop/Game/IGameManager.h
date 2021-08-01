#ifndef POOPPOP_GAME_IGAMEMANAGER_H_
#define POOPPOP_GAME_IGAMEMANAGER_H_

#include "../Fsm/StateMachine.h"

namespace fsm = ::pooppop::fsm;

namespace pooppop {
	namespace game {
		class IGameManager
		{
		public:
			inline static IGameManager* GetInstance() { return instance; }
			virtual fsm::StateMachine* GetStateMachine() = 0;
			virtual int Play() = 0;

		protected:
			void static SetInstance(IGameManager*);

			static IGameManager* instance;
		};
	}
}

#endif  // POOPPOP_GAME_IGAMEMANAGER_H_