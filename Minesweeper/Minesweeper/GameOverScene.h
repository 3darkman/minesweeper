#pragma once
#include "GameData.h"
#include "Scene.h"

namespace ks
{
	class GameOverScene : public Scene
	{
	public:
		GameOverScene(GameDataRef data);
		void Init() override;
		void HandleInput() override;
		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;
	private:
		GameDataRef data;
		sf::Text* gameOverText;
		sf::Text* hintText;
	};
}

