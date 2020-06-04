#include "InputManager.h"

bool ks::InputManager::IsSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(
			sprite.getPosition().x, 
			sprite.getPosition().y, 
			sprite.getGlobalBounds().width, 
			sprite.getGlobalBounds().height
		);

		if (tempRect.contains(this->GetMousePosition(window)))
		{
			return true;
		}
	}
	return false;
}

sf::Vector2i ks::InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
