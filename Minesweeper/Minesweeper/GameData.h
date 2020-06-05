#pragma once
#include "AssetManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "SFML/Graphics.hpp"

namespace ks
{
	struct GameData
	{
		SceneManager scenes;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
}
