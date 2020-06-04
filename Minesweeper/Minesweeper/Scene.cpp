#include "Scene.h"

void ks::Scene::Draw(float deltaTime)
{
	for (auto* go : gameObjects )
	{
		go->Draw(deltaTime);
	}
}