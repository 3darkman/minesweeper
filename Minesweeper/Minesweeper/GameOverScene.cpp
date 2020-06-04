#include "GameOverScene.h"
#include "DEFINITIONS.h"
#include "GameScene.h"

ks::GameOverScene::GameOverScene(GameDataRef data) : data(data)
{
}

void ks::GameOverScene::Init()
{
	this->data->assets.LoadFont(FONT_GAME_SANS_NAME, FONT_GAME_SANS_FILEPATH);

	this->gameOverText.setFont(this->data->assets.GetFont(FONT_GAME_SANS_NAME));
	this->gameOverText.setString("Game Over");
	
	auto x = SCREEN_WIDTH / 2 - this->gameOverText.getLocalBounds().width / 2;
	auto y = SCREEN_HEIGHT / 2 - this->gameOverText.getLocalBounds().height / 2;
	
	this->gameOverText.setPosition(x, y);
	
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

	this->data->window.draw(this->gameOverText);
	
	this->data->window.display();
}
