#include "MainMenuScene.h"

#include "DEFINITIONS.h"
#include "GameScene.h"

ks::MainMenuScene::MainMenuScene(GameDataRef data) : data(data)
{
	this->data->window.create(sf::VideoMode(INTERMEDIATE_SCREEN_WIDTH, INTERMEDIATE_SCREEN_HEIGHT), this->data->title, sf::Style::Close | sf::Style::Titlebar);
	this->data->window.setFramerateLimit(DEFAULT_FRAME_RATE);
}

void ks::MainMenuScene::Init()
{
	this->LoadAssets();

	this->logo.setTexture(this->data->assets.GetTexture(SPRITE_LOGO_NAME));
	this->AnchorObject(this->data->window, this->logo, this->logo.getGlobalBounds(), AnchorType::Top, sf::Vector2i(0, 40));

	const int margin = 20;
	
	int y = 40 + this->logo.getGlobalBounds().height + margin;

	this->beginnerButton.setTexture(this->data->assets.GetTexture(SPRITE_BEGINNER_BUTTON_NAME));
	this->AnchorObject(this->data->window, this->beginnerButton, this->beginnerButton.getGlobalBounds(), AnchorType::Top, sf::Vector2i(0, y));

	y += this->beginnerButton.getGlobalBounds().height + margin;
	
	this->intermediateButton.setTexture(this->data->assets.GetTexture(SPRITE_INTERMEDIATE_BUTTON_NAME));
	this->AnchorObject(this->data->window, this->intermediateButton, this->intermediateButton.getGlobalBounds(), AnchorType::Top, sf::Vector2i(0, y));

	y += this->intermediateButton.getGlobalBounds().height + margin;
	
	this->expertButton.setTexture(this->data->assets.GetTexture(SPRITE_EXPERT_BUTTON_NAME));
	this->AnchorObject(this->data->window, this->expertButton, this->expertButton.getGlobalBounds(), AnchorType::Top, sf::Vector2i(0, y));

	this->authorButton = new sf::Text(AUTHOR_NAME, this->data->assets.GetFont(FONT_JET_BRAINS_NAME), 15);
	this->AnchorObject(this->data->window, *this->authorButton, this->authorButton->getGlobalBounds(), AnchorType::Bottom, sf::Vector2i(0, -20));
	
}

void ks::MainMenuScene::HandleInput()
{
	sf::Event event;

	while (this->data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->data->window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (this->data->input.IsSpriteClicked(this->beginnerButton, sf::Mouse::Left, this->data->window))
			{
				this->data->difficult = GameDifficult::Beginner;
				this->data->scenes.AddScene(SceneRef(new GameScene(this->data)), true);
			}
			
			if(this->data->input.IsSpriteClicked(this->intermediateButton, sf::Mouse::Left, this->data->window))
			{
				this->data->difficult = GameDifficult::Intermediate;
				this->data->scenes.AddScene(SceneRef(new GameScene(this->data)), true);
			}

			if (this->data->input.IsSpriteClicked(this->expertButton, sf::Mouse::Left, this->data->window))
			{
				this->data->difficult = GameDifficult::Expert;
				this->data->scenes.AddScene(SceneRef(new GameScene(this->data)), true);
			}
		}
	}
}

void ks::MainMenuScene::Draw(float deltaTime)
{
	this->data->window.clear(sf::Color(45, 43, 43));

	this->data->window.draw(this->logo);
	this->data->window.draw(this->beginnerButton);
	this->data->window.draw(this->intermediateButton);
	this->data->window.draw(this->expertButton);
	this->data->window.draw(*this->authorButton);

	this->data->window.display();
}

void ks::MainMenuScene::LoadAssets()
{
	this->data->assets.LoadTexture(SPRITE_LOGO_NAME, SPRITE_LOGO_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BEGINNER_BUTTON_NAME, SPRITE_BEGINNER_BUTTON_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_INTERMEDIATE_BUTTON_NAME, SPRITE_INTERMEDIATE_BUTTON_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_EXPERT_BUTTON_NAME, SPRITE_EXPERT_BUTTON_FILEPATH);
	this->data->assets.LoadFont(FONT_JET_BRAINS_NAME, FONT_JET_BRAINS_FILEPATH);
}
