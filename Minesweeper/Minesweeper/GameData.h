#pragma once
#include "AssetManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SFML/Graphics.hpp"

namespace ks
{
	/**
	 * Game difficulty options.
	 *
	 * Used for various functions to control the size of the game screen
	 * and the grid.
	 */
	enum class GameDifficult
	{
		Intermediate,
		Beginner,
		Expert
	};

	/**
	 * Struct that stores the main game systems.
	 * used for the traffic of these systems between the classes of the game.
	 *
	 */
	struct GameData
	{
		/// Title to be used in the game window.
		std::string title;

		/// Reference to the game's managed scene system.
		SceneManager scenes;

		/// Reference to the game's window system.
		sf::RenderWindow window;

		/// Reference to the external asset management system.
		AssetManager assets;

		/// Reference to some utility functions with respect to game input.
		InputManager input;

		/// Current game difficulty.
		GameDifficult difficult;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
}
