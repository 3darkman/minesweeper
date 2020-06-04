#pragma once

namespace ks
{
	class GameObject
	{
	protected:
		int sortOrder;
	public:
		virtual ~GameObject() = default;
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(float deltaTime) = 0;

		bool operator <(const GameObject& other) const
		{
			return this->sortOrder < other.sortOrder;
		}
	};
}