#include "Grid.h"

#include <unordered_set>

#include "DEFINITIONS.h"


void ks::Grid::CreateBlocks()
{
	for (int x = 0; x < this->size.x; x++)
	{
		std::vector<GridBlock> vector;
		for (int y = 0; y < this->size.y; y++)
		{
			GridBlock block(this, sf::Vector2i(x, y), this->data);

			vector.push_back(block);
		}
		gridBlocks.push_back(vector);
	}
}

void ks::Grid::InitializeBlocks(const std::vector<sf::Vector2<int>>& bombs)
{
	for (auto bomb : bombs)
	{
		gridBlocks[bomb.x][bomb.y].SetType(BlockType::Bomb);
		for (int x = bomb.x-1; x <= bomb.x+1; x++)
		{
			if (x >=0 && x < GRID_COLUMNS)
			{
				for (int y = bomb.y - 1; y <= bomb.y+1; y++)
				{
					if (y >= 0 && y < GRID_ROWS && gridBlocks[x][y].GetType() != BlockType::Bomb)
					{
						gridBlocks[x][y].SetType(BlockType::Numbered);
						gridBlocks[x][y].AddNeighboringBomb();
					}
				}
			}
		}
	}

	for (int x = 0; x < this->size.x; x++)
	{
		for (int y = 0; y < this->size.y; y++)
		{
			gridBlocks[x][y].Init();
		}
	}
}

void ks::Grid::Init()
{
	auto bombs = this->DefineBombsPositions();
	
	this->CreateBlocks();

	this->InitializeBlocks(bombs);
	
}

void ks::Grid::Draw(float deltaTime)
{
	for (int x = 0; x < this->gridBlocks.size(); x++)
	{
		for (int y = 0; y < this->gridBlocks[x].size(); y++)
		{
			this->gridBlocks[x][y].Draw(deltaTime);
		}
	}
}

sf::Vector2f ks::Grid::GetPosition()
{
	return this->position;
}

std::vector<sf::Vector2i> ks::Grid::DefineBombsPositions()
{
	std::vector<sf::Vector2i> bombs;

	int bombsNumber = 0;

	do
	{
		int x = rand() % GRID_COLUMNS;
		int y = rand() % GRID_ROWS;
		sf::Vector2i position(x, y);

		auto results = std::find(bombs.begin(), bombs.end(), position);

		if (results == bombs.end())
		{
			bombs.push_back(position);
			bombsNumber++;
		}
	} while (bombsNumber < NUMBER_OF_BOMBS);

	return bombs;
}

ks::Grid::Grid(int columns, int rows, sf::Vector2f position, GameDataRef data) : data(data)
{
	this->size.x = columns;
	this->size.y = rows;
	this->position = position;
}
