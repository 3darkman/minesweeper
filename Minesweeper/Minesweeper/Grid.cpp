#include "Grid.h"
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

void ks::Grid::InitializeBlocks(const std::vector<sf::Vector2i>& bombs)
{
	for (auto bomb : bombs)
	{
		gridBlocks[bomb.x][bomb.y].SetType(BlockType::Bomb);

		std::vector<GridBlock*> neighbors;
		
		this->GetNeighbors(sf::Vector2i(bomb.x, bomb.y), neighbors);

		for (auto* neighbor : neighbors)
		{
			neighbor->SetType(BlockType::Numbered);
			neighbor->AddNeighboringBomb();
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
	this->revealedBlocks = 0;

	std::vector<sf::Vector2i> bombs;
	
	switch (this->data->difficult)
	{
	case GameDifficult::Intermediate:
		this->numberOfBombs = INTERMEDIATE_NUMBER_OF_BOMBS;
		break;
	case GameDifficult::Beginner:
		this->numberOfBombs = BEGINNER_NUMBER_OF_BOMBS;
		break;
	case GameDifficult::Expert:
		this->numberOfBombs = EXPERT_NUMBER_OF_BOMBS;
		break;
	}
	bombs = this->SelectRandomPositions(numberOfBombs);
	this->CreateBlocks();

	this->InitializeBlocks(bombs);
}

void ks::Grid::PutFlag(const sf::Vector2i position)
{
	auto gridPosition = this->WindowToGridPosition(position);

	this->gridBlocks[gridPosition.x][gridPosition.y].ToggleFlag();
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

bool ks::Grid::FlipNeighbors(ks::GridBlock& block)
{
	auto isAbomb = this->FlipBlock(block);
	this->revealedBlocks++;
	
	if (block.GetType() == BlockType::Empty)
	{
		std::vector<GridBlock*> neighbors;

		GetNeighbors(block.GetGridPosition(), neighbors);
		for (auto* neighbor : neighbors)
		{
			if (neighbor->GetState() == BlockState::Hidden)
			{
				if (neighbor->GetType() != BlockType::Bomb)
				{
					this->FlipNeighbors(*neighbor);
				}
			}
		}
	}
	return isAbomb;
}

sf::Vector2i ks::Grid::WindowToGridPosition(sf::Vector2i position) const
{
	return {
		(position.x - this->position.x) / GRID_BLOCK_SIZE, 
		(position.y - this->position.y) / GRID_BLOCK_SIZE
	};
}

bool ks::Grid::ProcessClick(sf::Vector2i position)
{
	const auto gridPosition = this->WindowToGridPosition(position);

	GridBlock* block = &gridBlocks[gridPosition.x][gridPosition.y];

	return this->FlipNeighbors(*block);
}

void ks::Grid::ShowsGridResult()
{
	for (int x = 0; x < this->size.x; x++)
	{
		for (int y = 0; y < this->size.y; y++)
		{
			gridBlocks[x][y].Show(false);
		}
	}
}

sf::Vector2i ks::Grid::GetPosition() const
{
	return this->position;
}

sf::IntRect ks::Grid::GetGlobalBounds() const
{
	return sf::IntRect(this->position, sf::Vector2i(this->size.x * GRID_BLOCK_SIZE, this->size.y * GRID_BLOCK_SIZE));
}

int ks::Grid::GetRevealedBlocks() const
{
	return this->revealedBlocks;
}

sf::Vector2i ks::Grid::GetSize() const
{
	return this->size;
}

int ks::Grid::GetNumberOfBombs() const
{
	return this->numberOfBombs;
}

std::vector<sf::Vector2i> ks::Grid::SelectRandomPositions(int numberOfPositions) const
{
	std::vector<sf::Vector2i> positions;

	int positionsSelected = 0;

	do
	{
		int x = rand() % this->size.x;
		int y = rand() % this->size.y;
		sf::Vector2i position(x, y);

		auto results = std::find(positions.begin(), positions.end(), position);

		if (results == positions.end())
		{
			positions.push_back(position);
			positionsSelected++;
		}
	} while (positionsSelected < numberOfPositions);

	return positions;
}

bool ks::Grid::FlipBlock(GridBlock& block) const
{
	const bool flipped = block.Flip(true);

	return flipped && block.GetType() == BlockType::Bomb;
}

void ks::Grid::GetNeighbors(sf::Vector2i position, std::vector<GridBlock*>& neighbors)
{
	for (int x = position.x - 1; x <= position.x + 1; x++)
	{
		if (x >= 0 && x < this->size.x)
		{
			for (int y = position.y - 1; y <= position.y + 1; y++)
			{
				if (y >= 0 && y < this->size.y && gridBlocks[x][y].GetType() != BlockType::Bomb)
				{
					if (x != position.x  || y != position.y)
					{
						neighbors.push_back(&gridBlocks[x][y]);
					}
				}
			}
		}
	}
}

ks::Grid::Grid(int columns, int rows, sf::Vector2i position, GameDataRef data) : data(data)
{
	this->size.x = columns;
	this->size.y = rows;
	this->position = position;
}