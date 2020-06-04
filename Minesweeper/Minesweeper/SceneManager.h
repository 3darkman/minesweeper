#pragma once
#include <memory>
#include <stack>


#include "Scene.h"

namespace ks
{
	typedef std::unique_ptr<Scene> SceneRef;
	
	class SceneManager
	{
	public:
		SceneManager() { }
		~SceneManager() { }

		void AddScene(SceneRef newScene, bool isReplacing = true);
		void RemoveScene();

		void ProcessSceneChanges();

		SceneRef& GetActiveScene();

	private:
		std::stack<SceneRef> scenes;
		SceneRef newScene;

		bool isRemoving;
		bool isAdding;
		bool isReplacing;
	};
}
