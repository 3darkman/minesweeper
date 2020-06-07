#pragma once
#include "GameData.h"
#include "Scene.h"

namespace ks
{
	/**
	 * Main menu game scene, in which the player can choose
	 * which game mode he wants to play.
	 */
	class MainMenuScene : public Scene
	{
	public:
		/**
		 * Default class constructor
		 *
		 * @param data Reference to the main game systems.
		 */
		MainMenuScene(GameDataRef data);

		/**
		 * Loads the assets needed for the scene and initializes
		 * its components.
		 */
		void Init() override;

		/**
		 * Manages all the necessary inputs for the scene.
		 * In the case of this scene, check if the player clicked
		 * with the mouse in one of the button options rendered in
		 * the window.
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

		/**
		 * Uses the external asset manager to load all that will be
		 * needed in the scene.
		 */
		void LoadAssets();

		/// Reference to the main game systems.
		GameDataRef data;

		/// Game logo that will be rendered in the window
		sf::Sprite logo;

		/// Button for beginner mode that will be rendered in the window
		sf::Sprite beginnerButton;

		/// Button for intermediate mode that will be rendered in the window
		sf::Sprite intermediateButton;

		/// Button for expert mode that will be rendered in the window
		sf::Sprite expertButton;

		/// Name of the author of the game that will be rendered on the screen
		sf::Text* authorButton;
	};
}