#pragma once

#include <SFML/Graphics.hpp>

namespace ks
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window);
		bool IsRectClicked(sf::IntRect rect, sf::Mouse::Button button, sf::RenderWindow& window, sf::Event::MouseButtonEvent event);
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}

