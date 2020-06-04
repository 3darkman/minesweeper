#pragma once
#include "GameObject.h"
#include "GridBlock.h"

namespace ks
{
	class Grid : public GameObject
	{
	public:
		Grid(int columns, int rows, sf::Vector2f position, GameDataRef data);
		void CreateBlocks();
		void InitializeBlocks(const std::vector<sf::Vector2<int>>& bombs);
		void Init() override;
		void Update(float deltaTime) override {};
		void Draw(float deltaTime) override;

		sf::Vector2f GetPosition();

	private:
		std::vector<sf::Vector2i> DefineBombsPositions();
		
		std::vector <std::vector<GridBlock> > gridBlocks;
		sf::Vector2f position;
		sf::Vector2i size;

		GameDataRef data;
	};
}

