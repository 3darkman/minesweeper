#include "GridBlock.h"
#include "DEFINITIONS.h"
#include "Grid.h"

void ks::GridBlock::Init()
{
	position.x = gridPosition.x * GRID_BLOCK_SIZE + this->gridParent->GetPosition().x;
	position.y = gridPosition.y * GRID_BLOCK_SIZE + this->gridParent->GetPosition().y;
	this->sprite.setPosition(position);
	ChangeState(BlockState::Hidden, false);
}

void ks::GridBlock::Draw(float deltaTime)
{
	this->data->window.draw(this->sprite);
}

void ks::GridBlock::ToggleFlag()
{
	if (this->state != BlockState::FaceUp)
	{
		this->ChangeState(this->state == BlockState::Flagged ?  BlockState::Hidden : BlockState::Flagged, false);
	}
}

bool ks::GridBlock::Flip(bool canExplodeBombs)
{
	if (this->state == BlockState::Hidden)
	{
		this->ChangeState(this->state == BlockState::Hidden ? BlockState::FaceUp : BlockState::Hidden, canExplodeBombs);
		return true;
	}
	return false;
}

void ks::GridBlock::Show(bool ignoreFlag)
{
	switch (this->state)
	{
	case BlockState::Hidden:
		this->ChangeState(BlockState::FaceUp, false);
		break;
	case BlockState::Flagged:
		if (ignoreFlag)
		{
			this->ChangeState(BlockState::FaceUp, false);
		}
		else
		{
			if (this->type != BlockType::Bomb)
			{
				this->ChangeState(BlockState::MissFlagged, false);
			}
		}
		break;
	}
}

void ks::GridBlock::SetType(BlockType type)
{
	this->type = type;
}

ks::BlockType ks::GridBlock::GetType() const
{
	return this->type;
}

ks::BlockState ks::GridBlock::GetState() const
{
	return this->state;
}

void ks::GridBlock::AddNeighboringBomb()
{
	if (this->neighboringBombs < 8)
	{
		this->neighboringBombs++;
	}
}

sf::Vector2i ks::GridBlock::GetGridPosition() const
{
	return this->gridPosition;
}

sf::Texture& ks::GridBlock::GetFaceUpTexture(bool canExplodeBombs) const
{
	sf::Texture* tex = nullptr;
	
	switch (this->type)
	{
	case BlockType::Empty:
		tex = &this->data->assets.GetTexture(SPRITE_BLOCK_EMPTY_NAME);
		break;
	case BlockType::Bomb:
		if (canExplodeBombs)
		{
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_BOMB_SPLASH_NAME);
		}
		else
		{
			tex = &this->data->assets.GetTexture(SPRITE_BLOCK_BOMB_NAME);
		}
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

void ks::GridBlock::ChangeSprite(bool canExplodeBombs)
{
	switch (this->state)
	{
	case BlockState::Hidden:
		this->sprite.setTexture(this->data->assets.GetTexture(SPRITE_BLOCK_HIDDEN_NAME));
		break;
	case BlockState::FaceUp:
		this->sprite.setTexture(this->GetFaceUpTexture(canExplodeBombs));
		break;
	case BlockState::Flagged:
		this->sprite.setTexture(this->data->assets.GetTexture(SPRITE_BLOCK_FLAG_NAME));
		break;
	case BlockState::MissFlagged:
		this->sprite.setTexture(this->data->assets.GetTexture(SPRITE_BLOCK_FLAG_MISS_NAME));
		break;
		
	}
}

void ks::GridBlock::ChangeState(BlockState newState, bool canExplodeBombs)
{
	this->state = newState;
	this->ChangeSprite(canExplodeBombs);
}