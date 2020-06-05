#pragma once
#include "SFML/Graphics.hpp"

namespace ks
{
	enum class AnchorType
	{
		Top,
		TopLeft,
		TopRight,
		Center,
		CenterLeft,
		CenterRight,
		Bottom,
		BottomLeft,
		BottomRight
	};
	
	class Scene
	{
	public:
		virtual ~Scene() = default;
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(float deltaTime) = 0;

		virtual void Pause() {}
		virtual void Resume() {}

		void AnchorObject(sf::RenderWindow& window, sf::Transformable& object, sf::FloatRect bounds, AnchorType anchor, sf::Vector2i offset) const;
	};
}
