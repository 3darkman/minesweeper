#pragma once
#include "GameObject.h"
#include "GridBlock.h"

namespace ks
{
	class Grid : public GameObject
	{
	public:
		Grid(int columns, int rows, sf::Vector2i position, GameDataRef data);
		void Init() override;
		void Update(float deltaTime) override {}
		void PutFlag(const sf::Vector2i position);;
		void Draw(float deltaTime) override;
		sf::Vector2i WindowToGridPosition(sf::Vector2i position) const;
		void ProcessClick(sf::Vector2i position);
		sf::Vector2i GetPosition() const;
		sf::IntRect GetGlobalBounds() const;

	private:
		std::vector<sf::Vector2i> DefineBombsPositions();
		void CreateBlocks();
		void InitializeBlocks(const std::vector<sf::Vector2i>& bombs);
		void FlipBlock(GridBlock& block);
		void FlipNeighbors(ks::GridBlock& block);
		void GetNeighbors(sf::Vector2i position, std::vector<GridBlock*>& neighbors);
		std::vector <std::vector<GridBlock> > gridBlocks;
		sf::Vector2i position;
		sf::Vector2i size;

		GameDataRef data;
	};
}

