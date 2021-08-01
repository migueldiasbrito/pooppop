#include "Scene.h"
#include "Renderer.h"

namespace engine = ::pooppop::sdl_game_engine;

bool engine::Scene::Open() {
	return true;
}

bool engine::Scene::Loop()
{
	/*ServiceLocator::getInputProvider()->updateEvents();

	if ((ServiceLocator::getInputProvider()->isClosing()))
		return false;*/

	HandleInput();
	Update();
	Draw();

	return true;
}

void engine::Scene::Close()
{
	int i, j;

	for (i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}

	gameObjects.clear();
}

void engine::Scene::Update()
{
	int i;
	float elapsedTime = 1.0f / FRAME_RATE;

	for (i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] != NULL)
		{
			if (!gameObjects[i]->Update(elapsedTime))
			{
				delete gameObjects[i];
				gameObjects.erase(gameObjects.begin() + i);
				i--;
			}
		}
	}
}

void engine::Scene::Draw()
{
	int i;

	Renderer::GetInstance()->Clear();

	for (i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] != NULL)
		{
			gameObjects[i]->Draw();
		}
	}

	Renderer::GetInstance()->DrawFinalize();
}

void engine::Scene::HandleInput() {

}
