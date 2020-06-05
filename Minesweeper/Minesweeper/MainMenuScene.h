#pragma once
#include "GameData.h"
#include "Scene.h"

namespace ks
{
	class MainMenuScene : public Scene
	{
	public:
		MainMenuScene(GameDataRef data);
		void Init() override;
		void HandleInput() override;
		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;
	private:
		void LoadAssets();
		
		GameDataRef data;

		sf::Sprite logo;
		sf::Sprite beginnerButton;
		sf::Sprite intermediateButton;
		sf::Sprite expertButton;
		sf::Text* authorButton;
	};
}