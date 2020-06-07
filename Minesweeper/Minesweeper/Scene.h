#pragma once
#include "SFML/Graphics.hpp"

namespace ks
{
	/**
	 * Positioning anchor options for objects that are rendered
	 */
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

	/**
	 * abstract class to be inherited when implementing a game scene.
	 * It is used by the scene manager.
	 */
	class Scene
	{
	public:
		virtual ~Scene() = default;
		
		/**
		 * Function performed as soon as the scene is loaded
		 */
		virtual void Init() = 0;
		
		/**
		 * Manages all the necessary inputs for the scene.
		 */
		virtual void HandleInput() = 0;
		
		/**
		 * This function performs at each frame. 
		 */
		virtual void Update(float deltaTime) {}
		
		/**
		 * Updates the rendering of the scene at each frame. Including
		 * rendering of its components.
		 *
		 * @param deltaTime Time passed from the last frame so far.
		 */
		virtual void Draw(float deltaTime) = 0;
		
		/**
		 * Function called when a new scene is loaded without replacing
		 * this scene.
		 */
		virtual void Pause() {}
		
		/**
		 * Function called when the current scene is removed and this
		 * scene is still loaded in the scene manager.
		 */
		virtual void Resume() {}

		/**
		 * Utility function to position the renderable objects
		 * correctly anchored in the current game window.
		 *
		 * @param window Reference to current game window.
		 * @param object Object that will have its position defined.
		 * @param bounds Rectangle in pixels, representing the space occupied by the object.
		 * @param anchor Type of anchor used to position the object in the window.
		 * @param offset offset space of the object in relation to the selected anchor.
		 */
		void AnchorObject(sf::RenderWindow& window, sf::Transformable& object, sf::FloatRect bounds, AnchorType anchor, sf::Vector2i offset) const;
	};
}
