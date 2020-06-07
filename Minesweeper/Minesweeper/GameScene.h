#pragma once
#include "GameData.h"
#include "Grid.h"
#include "Scene.h"

namespace ks
{
	/**
	 * Possible game states
	 *
	 * Used by the scene to enable or disable the player's input
	 * or to load the game over scene.
	 */
	enum class GameState
	{
		Running,
		Lose,
		Won
	};

	/**
	 * Main game scene. It contains the main logical components of the game,
	 * such as the minesweeper grid.
	 *
	 * This class is also responsible for managing all the player's input
	 * during a game.
	 */
	class GameScene : public Scene
	{
	public:
		/**
		 * Default class constructor
		 *
		 * @param data Reference to the main game systems.
		 */
		GameScene(GameDataRef data);
		
		~GameScene() override;

		/**
		 * Loads the assets needed for the scene and initializes
		 * its components.
		 *
		 * Creates the grid and window with the size based on the
		 * current difficulty of the game.
		 *
		 * The screen and grid sizes, as well as the number of bombs
		 * are defined in the DEFINITIONS.h file
		 */
		void Init() override;
		
		/**
		 * Manages all the necessary inputs for the scene.
		 *
		 * While the state is Running, the scene will only
		 * validate the clicks on the grid, showing the block
		 * when clicking with the left button and placing a flag
		 * when clicking with the right button, and the Escape key
		 * reloading the scene with a new grid.
		 *
		 * When the state is Won, any button clicked or the Enter
		 * key on the keyboard will return to the main scene
		 */
		void HandleInput() override;

		/**
		 * This function performs at each frame.
		 *
		 * If the game status is Lose, this function waits for a
		 * time set by PAUSE_TIME_AFTER_GAME_END to direct the game
		 * to the game over scene.
		 */
		void Update(float deltaTime) override;

		/**
		 * Updates the rendering of the scene at each frame. Including
		 * rendering of its components.
		 *
		 * @param deltaTime Time passed from the last frame so far.
		 */
		void Draw(float deltaTime) override;

	private:
		/**
		 * Uses the external asset manager to load all that will be
		 * needed in the scene.
		 */
		void LoadAssets() const;

		/**
		 * Creates the grid with the size based on the
		 * current difficulty of the game and initializes it.
		 *
		 * The grid size is defined in the DEFINITIONS.h file
		 *
		 * This function is called by the scene's Init function.
		 */
		void CreateGrid();

		/**
		 * Check if it is the end of the game and modify the state
		 * of the game accordingly.
		 *
		 * If the player's last click is a bomb, it changes the game
		 * state to Lose. If the player has already flipped over all
		 * the blocks that are not a bomb, it changes the game state
		 * to Won
		 *
		 * @param isLastClickABomb It must be true if the player's
		 * last click was on a bomb. Otherwise, false.
		 */
		void CheckEndGame(bool isLastClickABomb);

		/// Reference to the main game systems.
		GameDataRef data;

		/// Current game sate.
		GameState state;

		/// Clock to calculate past time. It is used to validate the
		/// break time after the game is over.
		sf::Clock clock;

		/// Reference to the grid of blocks essential to the game.
		Grid* grid = nullptr;

		/// Victory text that is rendered when the game state changes
		/// to Won.
		sf::Text* victoryText;

		/// Text that is rendered when the game state changes to Won.
		/// It tells the player which key to press to proceed.
		sf::Text* hintText;

		/// Logo of the game that is rendered in the scene.
		sf::Sprite logo;

		/// If true, it indicates that the pause time at the end of the game is over.
		bool canClickToRestart;
	};
}