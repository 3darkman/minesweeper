#pragma once
#include "GameData.h"
#include "Scene.h"

namespace ks
{
	/**
	 * Game over scene of the game. gives a message to the
	 * player and allows him to return to the main menu.
	 */
	class GameOverScene : public Scene
	{
	public:
		/**
		 * Default class constructor
		 *
		 * @param data Reference to the main game systems.
		 */
		GameOverScene(GameDataRef data);

		/**
		 * Loads the assets needed for the scene and initializes
		 * its components.
		 */
		void Init() override;

		/**
		 * Manages all the necessary inputs for the scene.
		 * In the case of this scene, check if the player clicked
		 * with the mouse or press the Enter key to return to the
		 * main menu.
		 */
		void HandleInput() override;

		/**
		 * Updates the rendering of the scene at each frame. Including
		 * rendering of its components.
		 *
		 * @param deltaTime Time passed from the last frame so far.
		 */
		void Draw(float deltaTime) override;
	private:
		/// Reference to the main game systems.
		GameDataRef data;

		/// Game over text that is rendered in the scene.
		sf::Text* gameOverText;

		/// Text that is rendered in the scene, containing a
		/// hint of which key to press for the player to return
		/// to the main menu.
		sf::Text* hintText;
	};
}

