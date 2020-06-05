#pragma once
#include "GameData.h"
#include "Grid.h"
#include "Scene.h"

namespace ks
{
	enum class GameState
	{
		Running,
		Paused,
		Lose,
		Won
	};
	
	class GameScene : public Scene
	{
	public:
		GameScene(GameDataRef data);

		void Init() override;
		void CheckEndGame(bool isLastClickABomb);
		void HandleInput() override;
		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;
	private:
		void LoadAssets() const;
		void CreateGrid();
		GameDataRef data;
		GameState state;
		
		sf::Clock clock;

		Grid* grid = nullptr;

		sf::Text* victoryText;
		sf::Text* hintText;

		sf::Sprite background;
		sf::Sprite logo;

		bool canClickToRestart;
	};
}
