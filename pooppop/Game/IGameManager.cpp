#include "IGameManager.h"

pooppop::game::IGameManager* pooppop::game::IGameManager::instance = nullptr;

void pooppop::game::IGameManager::SetInstance(pooppop::game::IGameManager* newinstance) {
	if (instance == nullptr) {
		instance = newinstance;
	}
}