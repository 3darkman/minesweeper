#include "Scene.h"

void ks::Scene::AnchorObject(sf::RenderWindow& window, sf::Transformable& object, sf::FloatRect bounds, AnchorType anchor, sf::Vector2i offset) const
{
	int x = 0, y = 0;
	switch (anchor)
	{
	case AnchorType::Top:
		x = window.getSize().x / 2 - bounds.width / 2;
		break;
	case AnchorType::TopRight:
		x = window.getSize().x - bounds.width;
		break;
	case AnchorType::Center:
		x = window.getSize().x / 2 - bounds.width / 2;
		y = window.getSize().y / 2 - bounds.height / 2;
		break;
	case AnchorType::CenterLeft:
		y = window.getSize().y / 2 - bounds.height / 2;
		break;
	case AnchorType::CenterRight:
		x = window.getSize().x - bounds.width;
		y = window.getSize().y / 2 - bounds.height / 2;
		break;
	case AnchorType::Bottom:
		x = window.getSize().x / 2 - bounds.width / 2;
		y = window.getSize().y - bounds.height;
		break;
	case AnchorType::BottomLeft:
		y = window.getSize().y - bounds.height;
		break;
	case AnchorType::BottomRight:
		x = window.getSize().x - bounds.width;
		y = window.getSize().y - bounds.height;
		break;
	}
	x += offset.x;
	y += offset.y;
	object.setPosition(x, y);
}
