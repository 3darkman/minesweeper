#pragma once
#include "AssetManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SFML/Graphics.hpp"

namespace ks
{
	enum class GameDifficult
	{
		Intermediate,
		Beginner,
		Expert
	};
	
	struct GameData
	{
		std::string title;
		SceneManager scenes;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
		GameDifficult difficult;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
}
