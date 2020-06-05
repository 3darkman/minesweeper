#pragma once
#include "GridBlock.h"

namespace ks
{
	/**
	 * Implementation of the grid of a minesweeper game by Kirlian Silvestre.
	 *
	 * It creates, types and manages its blocks that are represented by GridBlock objects.
	 */
	class Grid
	{
	public:
		/**
		 * Constructor
		 *
		 * @param columns Number of blocks that the grid will have horizontally
		 * @param rows Number of blocks that the grid will have vertically
		 * @param data Reference to the main game systems
		 */
		Grid(int columns, int rows, sf::Vector2i position, GameDataRef data);

		/**
		 * Initializes the grid by creating its blocks and setting its types.
		 */
		void Init();
		
		/**
		 * Place a flag on the block in the indicated position.
		 *
		 * @param position Pixel position relative to the window, where the block is.
		 */
		void PutFlag(const sf::Vector2i position);

		/**
		 * Draws the object and its children in the current window.
		 *
		 * @param deltaTime Time passed from the last frame so far.
		 */
		void Draw(float deltaTime);

		/**
		 * Converts 2d coordinates of the current window to grid coordinates.
		 *
		 * @return A pair of x and y coordinates representing the position of a grid block.
		 * if the passed position is not within the grid, it will return negative coordinates
		 * or greater than the size of blocks in the grid. 
		 */
		sf::Vector2i WindowToGridPosition(sf::Vector2i position) const;
		
		/**
		 * Processes the click in the grid, obtaining the block clicked and flipping it
		 * if it is still hidden and without a flag. if it is empty, flip the neighboring
		 * blocks that are not a bomb.
		 *
		 * @param position Pixel position relative to the window, where the block is.
		 * @return If the clicked block is a bomb, it returns true, it returns false otherwise.
		 */
		bool ProcessClick(sf::Vector2i position);

		/**
		 * Flip all the blocks that have not yet been flipped or have a flag.
		 * If there is a flag on a block that is not a bomb, the flag will
		 * be marked as an error.
		 */
		void ShowsGridResult();
		
		/**
		 * Returns the grid position in the window, based on its top left.
		 */
		sf::Vector2i GetPosition() const;
		/**
		 * Obtain a rectangular representation of the grid, based on its
		 * position on the window and the number of blocks the grid has.
		 */
		sf::IntRect GetGlobalBounds() const;

		int GetRevealedBlocks();

	private:
		/**
		 * Randomly select a specified number of grid positions
		 *
		 * @param numberOfPositions Number of positions to be selected
		 * @return A vector containing pairs of x and y coordinates
		 */
		std::vector<sf::Vector2i> SelectRandomPositions(int numberOfPositions) const;

		/**
		 *	Creates all GridBlock instances according to the grid size.
		 */
		void CreateBlocks();

		/**
		 * Defines the types of all instances of the grid blocks and initializes them.
		 *
		 * @param bombs Container containing all bombs positions on the grid.
		 */
		void InitializeBlocks(const std::vector<sf::Vector2i>& bombs);

		/**
		 * Flip a block and if it is a bomb, the game is over.
		 *
		 * @param block	Reference to the block to be flipped.
		 * @return If the flipped block is a bomb, it returns true, it returns false otherwise.
		 */
		bool FlipBlock(GridBlock& block) const;

		/**
		 * Flip the current block, and if it is empty, flip all neighbors that are not a bomb.
		 *
		 * @param block The current block
		 * @return If the current block is a bomb, it returns true, it returns false otherwise.
		 */
		bool FlipNeighbors(ks::GridBlock& block);

		/**
		 * Obtain blocks neighboring a grid position.
		 *
		 * @param[in] position Position of the block from which the neighboring blocks
		 * are to be obtained
		 * @param[out] neighbors Vector containing the neighboring blocks found.
		 */
		void GetNeighbors(sf::Vector2i position, std::vector<GridBlock*>& neighbors);

		/// All blocks belonging to the grid that are instantiated through the CreateBlocks function.
		std::vector <std::vector<GridBlock> > gridBlocks;

		/// the grid position in the window, based on its top left.
		sf::Vector2i position;

		/// Number of blocks that the grid contains horizontally and vertically.
		sf::Vector2i size;

		/// Reference to the main game systems
		GameDataRef data;

		///amount of clicked and revealed blocks
		int revealedBlocks;
	};
}

