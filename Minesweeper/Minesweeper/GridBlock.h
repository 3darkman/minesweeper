#pragma once
#include "GameData.h"

namespace ks
{
	struct GameData;
	class Grid;

	enum class BlockType
	{
		Empty,
		Bomb,
		Numbered
	};

	enum class BlockState
	{
		Hidden,
		FaceUp,
		Flagged,
		MissFlagged
	};
	
	class GridBlock
	{
	public:
		GridBlock(Grid* grid, sf::Vector2i gridPosition, BlockType type, GameDataRef data);
		GridBlock(Grid* grid, sf::Vector2i gridPosition, GameDataRef data);
		void Init();
		void Draw(float deltaTime);
		void ToggleFlag();
		bool Flip(bool canExplodeBombs);
		void Show(bool ignoreFlag);
		void SetType(BlockType type);
		BlockType GetType() const;
		BlockState GetState() const;
		void AddNeighboringBomb();
		sf::Vector2i GetGridPosition() const;
				
	private:
		sf::Texture& GetFaceUpTexture(bool canExplodeBombs) const;
		void ChangeSprite(bool canExplodeBombs);
		void ChangeState(BlockState newState, bool canExplodeBombs);
		BlockType type;
		int neighboringBombs;
		BlockState state;
		Grid* gridParent;
		GameDataRef data;
		sf::Sprite sprite;
		sf::Vector2i gridPosition;
		sf::Vector2f position;
	};
}

