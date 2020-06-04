#pragma once
#include <iostream>
#include <set>

#include "GameObject.h"

namespace ks
{
	class Scene
	{
	protected:
		std::multiset<GameObject*> gameObjects;
	public:
		virtual ~Scene() = default;
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(float deltaTime) = 0;

		virtual void Pause() {}
		virtual void Resume() {}
	};
}
