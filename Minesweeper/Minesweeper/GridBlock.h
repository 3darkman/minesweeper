#pragma once
#include "GameData.h"

namespace ks
{
	class Grid;
	/**
	 * Types of grid blocks that are used to know which sprite should
	 * be shown when the player clicks on the block
	 */
	enum class BlockType
	{
		Empty,
		Bomb,
		/// Used when there are bombs near the block
		Numbered
	};

	/**
	 * Block status options. They are mainly used to find out what
	 * kind of interaction the player can make with them.
	 */
	enum class BlockState
	{
		///Initial state of all blocks
		Hidden,
		/// Block state after being clicked by the player.
		FaceUp,
		/// Block state for when the player signals it with
		/// a flag to prevent the block from being clickable.
		Flagged,
		/// it is only used at the end of the game, if the player
		/// loses and has placed a flag on a block that is not a bomb.
		MissFlagged
	};

	/**
	 * Implementation of the grid block for the game. Responsible for
	 * maintaining the consistency of your state and rendering the
	 * correct image based on your state and type.
	 */
	class GridBlock
	{
	public:
		/**
		 * Class constructor.
		 *
		 * @param grid Reference to the grid to which this block belongs
		 * @param gridPosition Vector informing in which column and which
		 * line of the grid this block will be.
		 * @param type Type of this block
		 * @param data Reference to the main game systems
		 */
		GridBlock(Grid* grid, sf::Vector2i gridPosition, BlockType type, GameDataRef data);
		
		/**
		 * Class constructor. The type is set to empty by default.
		 *
		 * @param grid Reference to the grid to which this block belongs
		 * @param gridPosition Vector informing in which column and which
		 * line of the grid this block will be.
		 * @param data Reference to the main game systems
		 */
		GridBlock(Grid* grid, sf::Vector2i gridPosition, GameDataRef data);

		/**
		 * Initializes the block, defining its correct position on the
		 * grid to be rendered in the window.
		 */
		void Init();

		/**
		 * Renders this block in the window
		 */
		void Draw(float deltaTime);

		/**
		 * Changes the flagged state of the block. If he has no flag,
		 * put a flag, otherwise, remove the flag.
		 *
		 * Only works if this block is still in a different state
		 * from the FaceUp
		 */
		void ToggleFlag();

		/**
		 * If the current state of the block is Hidden, changes the
		 * state of the block to FaceUp.
		 *
		 * @return If the current state of the block is Hidden, it
		 * returns True, otherwise, False
		 */
		bool Flip(bool canExplodeBombs);

		/**
		 * Changes the block state to FaceUp, regardless of his
		 * current state
		 *
		 * @param ignoreFlag If true, it also changes the state of the
		 * block that is in the Flagged state. Otherwise, it will only
		 * change the state from Flagged to MissFlagged,  and only if
		 * the block is not a Bomb type.
		 */
		void Show(bool ignoreFlag);

		/**
		 * Defines the type of the block. If the block state is already
		 * FaceUp, modify your sprite.
		 *
		 * @param type New block type
		 */
		void SetType(BlockType type);

		/**
		 * Informs the block that there is one more bomb around it.
		 *
		 * Is used to know which numbered sprite should be shown when
		 * the block state changes to FaceUp
		 */
		void AddNeighboringBomb();

		/**
		 * Get the current type of the block.
		 *
		 * @return the currente type of the block
		 */
		BlockType GetType() const;

		/**
		 * Get the current state of the block.
		 *
		 * @return the currente state of the block
		 */
		BlockState GetState() const;

		/**
		 * Obtain the column and the line that this block
		 * is in the grid.
		 *
		 * @return Vector containing the value of the column in x
		 * and the value of the line in y.
		 */
		sf::Vector2i GetGridPosition() const;
				
	private:
		/**
		 * Get the texture to be shown when the state of the block
		 * is FaceUp
		 *
		 * @param canExplodeBombs If true and the block type is bomb,
		 * an splash bomb texture will be returned.
		 *
		 * @return The texture corresponding to the type of the block.
		 * If it does not exist in the external asset library, it will
		 * return a null pointer.
		 */
		sf::Texture& GetFaceUpTexture(bool canExplodeBombs) const;

		/**
		 * Changes the sprite to be rendered from the block according
		 * to its type and state.
		 *
		 * @param canExplodeBombs If true and the block type is bomb,
		 * the sprite will be changed to an splash bomb.
		 */
		void ChangeSprite(bool canExplodeBombs);

		/**
		 * Changes the current state of the block and updates the
		 * sprite that will be rendered in the window.
		 *
		 * @param newState New state of this block.
		 *
		 * @param canExplodeBombs If true and the block type is bomb,
		 * the sprite will be changed to an splash bomb.
		 */
		void ChangeState(BlockState newState, bool canExplodeBombs);

		/// Current type of this block
		BlockType type;

		/// Number of bombs around the block
		int neighboringBombs;

		/// Current state of this block
		BlockState state;

		/// Reference to the grid to which this block belongs
		Grid* gridParent;

		/// Reference to the main game systems
		GameDataRef data;

		/// Sprite that will be rendered in the window,
		/// representing this block.
		sf::Sprite sprite;

		/// Vector informing in which column and which
		/// line of the grid this block will be.
		sf::Vector2i gridPosition;

		/// position, containing the x and y in pixels,
		/// of this block in the window
		sf::Vector2f position;
	};
}

