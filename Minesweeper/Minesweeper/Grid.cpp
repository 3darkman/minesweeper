#include "Grid.h"
#include "DEFINITIONS.h"
#include "GameOverScene.h"

/**
 *	Creates all GridBlock instances according to the grid size.
 */
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

/**
 * Defines the types of all instances of the grid blocks and initializes them.
 *
 * @param bombs Container containing all bombs positions on the grid.
 */
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

/**
 * Initializes the grid by creating its blocks and setting its types.
 */
void ks::Grid::Init()
{
	auto bombs = this->DefineBombsPositions();
	
	this->CreateBlocks();

	this->InitializeBlocks(bombs);
}

/**
 * Place a flag on the block in the indicated position.
 *
 * @param position Pixel position relative to the window, where the block is.
 */
void ks::Grid::PutFlag(const sf::Vector2i position)
{
	auto gridPosition = this->WindowToGridPosition(position);

	this->gridBlocks[gridPosition.x][gridPosition.y].ToggleFlag();
}

/**
 * Draws the object and its children in the current window.
 *
 * @param deltaTime Time passed from the last frame so far.
 */
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

void ks::Grid::FlipNeighbors(ks::GridBlock& block)
{
	this->FlipBlock(block);
	
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
}

sf::Vector2i ks::Grid::WindowToGridPosition(sf::Vector2i position) const
{
	return {
		(position.x - this->position.x) / GRID_BLOCK_SIZE, 
		(position.y - this->position.y) / GRID_BLOCK_SIZE
	};
}

void ks::Grid::ProcessClick(sf::Vector2i position)
{
	const auto gridPosition = this->WindowToGridPosition(position);

	GridBlock* block = &gridBlocks[gridPosition.x][gridPosition.y];

	this->FlipNeighbors(*block);
}

sf::Vector2i ks::Grid::GetPosition() const
{
	return this->position;
}

sf::IntRect ks::Grid::GetGlobalBounds() const
{
	return sf::IntRect(this->position, sf::Vector2i(GRID_COLUMNS * GRID_BLOCK_SIZE, GRID_ROWS * GRID_BLOCK_SIZE));
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

void ks::Grid::FlipBlock(GridBlock& block)
{
	bool flipped = block.Flip(true);

	if (flipped && block.GetType() == BlockType::Bomb)
	{
		this->data->scenes.AddScene(SceneRef(new GameOverScene(this->data)), true);
	}
}

void ks::Grid::GetNeighbors(sf::Vector2i position, std::vector<GridBlock*>& neighbors)
{
	for (int x = position.x - 1; x <= position.x + 1; x++)
	{
		if (x >= 0 && x < GRID_COLUMNS)
		{
			for (int y = position.y - 1; y <= position.y + 1; y++)
			{
				if (y >= 0 && y < GRID_ROWS && gridBlocks[x][y].GetType() != BlockType::Bomb)
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