#include "Game.h"
#include <iostream>
#include "MainMenuScene.h"
#include <SFML/Window.hpp>

ks::Game::Game(int width, int height, std::string title)
{
	srand(static_cast<unsigned int>(time(0)));
	this->data->title = title;
	this->data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

	this->data->scenes.AddScene(SceneRef(new MainMenuScene(this->data)), true);
	
	this->Run();
}

void ks::Game::Run()
{
	float newTime, frameTime;

	float currentTime = this->clock.getElapsedTime().asSeconds();

	float accumulator = 0.0f;

	while (this->data->window.isOpen())
	{
		this->data->scenes.ProcessSceneChanges();
		
		newTime = this->clock.getElapsedTime().asSeconds();
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
