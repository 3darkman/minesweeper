#include "GridBlock.h"
#include "DEFINITIONS.h"
#include "Grid.h"

void ks::GridBlock::Init()
{
	position.x = gridPosition.x * GRID_BLOCK_SIZE + this->gridParent->GetPosition().x;
	position.y = gridPosition.y * GRID_BLOCK_SIZE + this->gridParent->GetPosition().y;
	sortOrder = 1;
	this->sprite.setPosition(position);
	ChangeState(BlockState::FaceUp);
}

void ks::GridBlock::Draw(float deltaTime)
{
	this->data->window.draw(this->sprite);
}

void ks::GridBlock::Flag(bool isFlagged)
{
	if (this->state != BlockState::FaceUp)
	{
		this->ChangeState(isFlagged ? BlockState::Flagged : BlockState::Hidden);
	}
}

void ks::GridBlock::Flip()
{
	if (this->state != BlockState::Flagged)
	{
		this->ChangeState(this->state == BlockState::Hidden ? BlockState::FaceUp : BlockState::Hidden);
	}	
}

void ks::GridBlock::SetType(BlockType type)
{
	this->type = type;
}

ks::BlockType ks::GridBlock::GetType()
{
	return this->type;
}

void ks::GridBlock::AddNeighboringBomb()
{
	if (this->neighboringBombs < 8)
	{
		this->neighboringBombs++;
	}
}

sf::Texture& ks::GridBlock::GetFaceUpTexture()
{
	sf::Texture* tex = nullptr;
	
	switch (this->type)
	{
	case BlockType::Empty:
		tex = &this->data->assets.GetTexture(SPRITE_BLOCK_EMPTY_NAME);
		break;
	case BlockType::Bomb:
		tex = &this->data->assets.GetTexture(SPRITE_BLOCK_BOMB_NAME);
		break;
	case BlockType::Numbered:
		switch (this->neighboringBombs)
		{
		case 1:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_01_NAME);
			break;
		case 2:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_02_NAME);
			break;
		case 3:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_03_NAME);
			break;
		case 4:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_04_NAME);
			break;
		case 5:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_05_NAME);
			break;
		case 6:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_06_NAME);
			break;
		case 7:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_07_NAME);
			break;
		case 8:
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_08_NAME);
			break;
		}
		break;
	}
	
	return *tex;
}

ks::GridBlock::GridBlock(Grid* grid, sf::Vector2i gridPosition, BlockType type, GameDataRef data) : data(data)
{
	this->neighboringBombs = 0;
	this->gridParent = grid;
	this->type = type;
	this->gridPosition = gridPosition;
}

ks::GridBlock::GridBlock(Grid* grid, sf::Vector2i gridPosition, GameDataRef data) : data(data)
{
	this->neighboringBombs = 0;
	this->gridParent = grid;
	this->type = BlockType::Empty;
	this->gridPosition = gridPosition;
}

void ks::GridBlock::ChangeState(BlockState newState)
{
	this->state = newState;
	switch (this->state)
	{
	case BlockState::Hidden:
		this->sprite.setTexture(this->data->assets.GetTexture(SPRITE_BLOCK_HIDDEN_NAME));
		break;
	case BlockState::FaceUp:
		this->sprite.setTexture(this->GetFaceUpTexture());
		break;
	case BlockState::Flagged:
		this->sprite.setTexture(this->data->assets.GetTexture(SPRITE_BLOCK_FLAG_NAME));
		break;
	}
}
