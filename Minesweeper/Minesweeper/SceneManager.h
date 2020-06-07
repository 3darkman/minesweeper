#pragma once
#include <stack>

#include "Scene.h"

namespace ks
{
	typedef std::unique_ptr<Scene> SceneRef;
	
	/**
	 * Class responsible for managing the scenes, maintaining a flow of
	 * which are loaded, which are destroyed and which are on standby
	 */
	class SceneManager
	{
	public:
		SceneManager() { }
		~SceneManager() { }

		/**
		 * Prepares a new scene to be added to the scene stack
		 *
		 * @param newScene References the new scene that will be added
		 * @param isReplacing if true, the current scene will be removed from
		 * the stack. Otherwise, the current scene will be paused until the
		 * new scene is removed.
		 */
		void AddScene(SceneRef newScene, bool isReplacing = true);

		/**
		 * Prepare the current scene to be removed of the stack
		 */
		void RemoveScene();

		/**
		 * Processes all changes prepared by the AddScene and RemoveScene
		 * functions
		 */
		void ProcessSceneChanges();

		/**
		 * Get the current scene which is at the top of the scene stack.
		 */
		SceneRef& GetActiveScene();

	private:
		/// Stack of scenes still loaded into the game
		std::stack<SceneRef> scenes;

		/// New scene to be added to the scene stack when the
		/// ProcessSceneChanges function is called again.
		SceneRef newScene;

		/// Tells whether the ProcessSceneChanges function should
		/// remove a scene from the stack. Is defined when the RemoveScene
		/// function is called.
		bool isRemoving = false;

		/// Tells whether the ProcessSceneChanges function should
		/// to add a newScene to the stack. Is defined when the AddScene
		/// function is called.
		bool isAdding = false;

		/// Tells the ProcessSceneChanges function whether to add a new
		/// scene to the scene stack, the current scene should be replaced.
		bool isReplacing = false;
	};
}
