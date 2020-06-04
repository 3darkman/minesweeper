#pragma once
#include "GameObject.h"

namespace ks
{
	class ButtonGameObject : public GameObject
	{
	public:
		void Init() override;
		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;

	private:
		
	};
}

