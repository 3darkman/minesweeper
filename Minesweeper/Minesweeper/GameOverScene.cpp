#include "GameOverScene.h"
#include "DEFINITIONS.h"
#include "GameScene.h"

ks::GameOverScene::GameOverScene(GameDataRef data) : data(data)
{
}

void ks::GameOverScene::Init()
{
	this->data->assets.LoadFont(FONT_GAME_SANS_NAME, FONT_GAME_SANS_FILEPATH);

	this->gameOverText = new sf::Text("Game Over", this->data->assets.GetFont(FONT_GAME_SANS_NAME));
	this->AnchorObject(this->data->window, *this->gameOverText, this->gameOverText->getLocalBounds(), AnchorType::Center, sf::Vector2i(0, 20));

	this->hintText = new sf::Text("press <Enter>", this->data->assets.GetFont(FONT_GAME_SANS_NAME), 10);
	this->AnchorObject(this->data->window, *this->hintText, this->hintText->getLocalBounds(), AnchorType::Center, sf::Vector2i(0, 60));
	this->hintText->setStyle(sf::Text::Style::Italic);
}

void ks::GameOverScene::HandleInput()
{
	sf::Event event;
	
	while (this->data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->data->window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				this->data->scenes.AddScene(SceneRef(new GameScene(this->data)), true);
			}
		}
	}
}

void ks::GameOverScene::Update(float deltaTime)
{
}

void ks::GameOverScene::Draw(float deltaTime)
{
	this->data->window.clear(sf::Color::Black);

	this->data->window.draw(*this->gameOverText);
	this->data->window.draw(*this->hintText);
	
	this->data->window.display();
}
