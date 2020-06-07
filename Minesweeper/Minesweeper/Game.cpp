#include "Game.h"
#include "MainMenuScene.h"
#include <SFML/Window.hpp>
#include "DEFINITIONS.h"

ks::Game::Game(int width, int height, std::string title)
{
	srand(static_cast<unsigned int>(time(0)));
	this->data->title = title;
	this->data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	this->data->window.setFramerateLimit(DEFAULT_FRAME_RATE);
	
	this->data->scenes.AddScene(SceneRef(new MainMenuScene(this->data)), true);
	
	this->Run();
}

void ks::Game::Run() const
{
	float newTime, frameTime, drawTime;

	float currentTime = this->clock.getElapsedTime().asSeconds();

	while (this->data->window.isOpen())
	{
		this->data->scenes.ProcessSceneChanges();
		
		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		currentTime = newTime;

		this->data->scenes.GetActiveScene()->HandleInput();
		this->data->scenes.GetActiveScene()->Update(frameTime);

		newTime = this->clock.getElapsedTime().asSeconds();
		drawTime = newTime - currentTime;
		
		this->data->scenes.GetActiveScene()->Draw(drawTime);
	}
}