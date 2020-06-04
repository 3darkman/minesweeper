#include "Game.h"

#include "GameScene.h"

ks::Game::Game(int width, int height, std::string title)
{
	this->data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

	this->data->scenes.AddScene(SceneRef(new GameScene(this->data)));
	
	this->Run();
}

void ks::Game::Run()
{
	float newTime, frameTime;

	float currentTime = this->_clock.getElapsedTime().asSeconds();

	float accumulator = 0.0f;

	while (this->data->window.isOpen())
	{
		this->data->scenes.ProcessSceneChanges();
		
		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= deltaTime)
		{
			this->data->scenes.GetActiveScene()->HandleInput();
			this->data->scenes.GetActiveScene()->Update(deltaTime);

			accumulator -= deltaTime;
		}

		float interpolation = accumulator / deltaTime;
		this->data->scenes.GetActiveScene()->Draw(interpolation);
	}
}
