#pragma once

#include <SFML/Graphics.hpp>

namespace ks
{
	/**
	 * Utility class with some functions that assist in
	 * the management of player inputs.
	 */
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		/**
		 * Checks if a mouse click was made and if it was on a specific sprite
		 *
		 * @param sprite The sprite on which you want to check if the click was made.
		 * @param button Which button is specifically checking.
		 * @param window Reference to current game window.
		 *
		 * @return true, if the click with the specified button happened within
		 * the boundaries of the reported sprite. otherwise, it returns false.
		 */
		bool IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window);

		/**
		 * Checks if a mouse click was made and if it was on a specific area
		 * 
		 * @param rect Rectangle in pixels, relative to the window, in which we must verify if the click was made.
		 * @param button Which button is specifically checking.
		 * @param window Reference to current game window.
		 * @param event Current mouse click event
		 *
		 * @return true, if the click with the specified button happened within
		 * the boundaries of the reported rectangle. otherwise, it returns false.
		 */
		bool IsRectClicked(sf::IntRect rect, sf::Mouse::Button button, sf::RenderWindow& window, sf::Event::MouseButtonEvent event);

		/**
		 * Get the current mouse position
		 *
		 * @param window Reference to current game window.
		 *
		 * @return Vector containing x and y in pixels of the mouse position
		 * in relation to the informed window.
		 */
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}

