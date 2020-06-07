#pragma once
#include <string>
#include "GameData.h"

namespace ks
{
	/**
	 * Class responsible for maintaining the default game loop and updating
	 * the currently active scene.
	 * 
	 */
	class Game
	{
	public:
		/**
		 * Class constructor. After instantiating the class, the game loop 
		 * starts.
		 *
		 * @param width Initial game screen width
		 * @param height Initial game screen height
		 * @param title Initial game screen title
		 */
		Game(int width, int height, std::string title);

	private:
		/// standard time that a frame should last to maintain the fps standard
		const float deltaTime = 1.0f / 60.0f;

		sf::Clock clock;

		
		GameDataRef data = std::make_shared<GameData>();


		/**
		 * Performs the standard game loop and updates the scenes at each frame,
		 * keeping the number of frames per second stable.
		 */
		void Run();
	};
}

