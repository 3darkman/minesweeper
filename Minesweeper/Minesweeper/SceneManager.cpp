#include "SceneManager.h"

void ks::SceneManager::AddScene(SceneRef newScene, bool isReplacing)
{
	this->isAdding = true;
	this->isReplacing = isReplacing;
	
	this->newScene = std::move(newScene);
}

void ks::SceneManager::RemoveScene()
{
	this->isRemoving = true;
}

void ks::SceneManager::ProcessSceneChanges()
{
	if (this->isRemoving && !this->scenes.empty())
	{
		this->scenes.pop();

		if (!this->scenes.empty())
		{
			this->scenes.top()->Resume();
		}
		this->isRemoving = false;
	}

	if (this->isAdding)
	{
		if (!this->scenes.empty())
		{
			if (this->isReplacing)
			{
				this->scenes.pop();
			}
			else
			{
				this->scenes.top()->Pause();
			}
		}
		this->scenes.push(std::move(this->newScene));
		this->scenes.top()->Init();
		this->isAdding = false;
	}
}

ks::SceneRef& ks::SceneManager::GetActiveScene()
{
	return this->scenes.top();
}



