#pragma once
#include "GameData.h"
#include "Grid.h"
#include "Scene.h"

namespace ks
{
	class GameScene : public Scene
	{
	public:
		GameScene(GameDataRef data);
		

		void Init() override;
		void HandleInput() override;
		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;
	private:
		void LoadAssets();

		GameDataRef data;
		sf::Clock clock;

		Grid* grid = nullptr;
	};
}

