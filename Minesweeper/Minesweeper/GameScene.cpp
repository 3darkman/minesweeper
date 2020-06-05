#include "GameScene.h"
#include "DEFINITIONS.h"
#include "GameOverScene.h"

ks::GameScene::GameScene(GameDataRef data) : data(data)
{
	
}

void ks::GameScene::LoadAssets() const
{
	this->data->assets.LoadTexture(SPRITE_BLOCK_EMPTY_NAME, SPRITE_BLOCK_EMPTY_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_BOMB_NAME, SPRITE_BLOCK_BOMB_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_HIDDEN_NAME, SPRITE_BLOCK_HIDDEN_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_BOMB_SPLASH_NAME, SPRITE_BLOCK_BOMB_SPLASH_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_FLAG_NAME, SPRITE_BLOCK_FLAG_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_FLAG_MISS_NAME, SPRITE_BLOCK_FLAG_MISS_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_01_NAME, SPRITE_BLOCK_01_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_02_NAME, SPRITE_BLOCK_02_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_03_NAME, SPRITE_BLOCK_03_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_04_NAME, SPRITE_BLOCK_04_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_05_NAME, SPRITE_BLOCK_05_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_06_NAME, SPRITE_BLOCK_06_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_07_NAME, SPRITE_BLOCK_07_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_08_NAME, SPRITE_BLOCK_08_FILEPATH);
	this->data->assets.LoadFont(FONT_GAME_SANS_NAME, FONT_GAME_SANS_FILEPATH);
}

void ks::GameScene::Init()
{
	this->LoadAssets();

	state = GameState::Running;

	this->grid = new Grid(GRID_COLUMNS, GRID_ROWS, sf::Vector2i(0, 88), this->data);
	this->grid->Init();

	this->victoryText = new sf::Text("You Won!", this->data->assets.GetFont(FONT_GAME_SANS_NAME));
	this->AnchorObject(this->data->window, *this->victoryText, this->victoryText->getLocalBounds(), AnchorType::Top, sf::Vector2i(0, 20));

	this->hintText = new sf::Text("press <Enter>", this->data->assets.GetFont(FONT_GAME_SANS_NAME), 10);
	this->AnchorObject(this->data->window, *this->hintText, this->hintText->getLocalBounds(), AnchorType::Top, sf::Vector2i(0, 60));
	this->hintText->setStyle(sf::Text::Style::Italic);
} 

void ks::GameScene::CheckEndGame(bool isLastClickABomb)
{
	if (isLastClickABomb)
	{
		this->grid->ShowsGridResult();
		this->clock.restart();
		this->state = GameState::Lose;
	}
	else
	{
		if (this->grid->GetRevealedBlocks() >= ((GRID_COLUMNS * GRID_ROWS) - NUMBER_OF_BOMBS))
		{
			this->state = GameState::Won;
		}
	}
}

void ks::GameScene::HandleInput()
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
			if (this->state == GameState::Running)
			{
				if (this->data->input.IsRectClicked(this->grid->GetGlobalBounds(), sf::Mouse::Left, this->data->window, event.mouseButton))
				{
					bool isABomb = this->grid->ProcessClick(this->data->input.GetMousePosition(this->data->window));

					CheckEndGame(isABomb);
				}

				if (this->data->input.IsRectClicked(this->grid->GetGlobalBounds(), sf::Mouse::Right, this->data->window, event.mouseButton))
				{
					this->grid->PutFlag(this->data->input.GetMousePosition(this->data->window));
				}
			}
		}

		if (this->state == GameState::Won)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					this->data->scenes.AddScene(SceneRef(new GameScene(this->data)), true);
				}
			}
		}
	}
}

void ks::GameScene::Update(float deltaTime)
{
	if (this->state == GameState::Lose)
	{
		if(this->clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOW_GAME_OVER)
		{
			this->data->scenes.AddScene(SceneRef(new GameOverScene(this->data)), true);
		}
	}
	
}

void ks::GameScene::Draw(float deltaTime)
{
	this->data->window.clear(sf::Color::Black);

	this->grid->Draw(deltaTime);

	if (this->state == GameState::Won)
	{
		this->data->window.draw(*this->victoryText);
		this->data->window.draw(*this->hintText);
	}

	this->data->window.display();
}