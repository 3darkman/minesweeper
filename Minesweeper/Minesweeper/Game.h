#pragma once
#include <string>
#include "GameData.h"

namespace ks
{
	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		const float deltaTime = 1.0f / 60.0f;

		sf::Clock _clock;

		GameDataRef data = std::make_shared<GameData>();

		void Run();
	};
}

