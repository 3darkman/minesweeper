#include "GameScene.h"
#include "DEFINITIONS.h"

ks::GameScene::GameScene(GameDataRef data) : data(data)
{
}

void ks::GameScene::LoadAssets()
{
	this->data->assets.LoadTexture(SPRITE_BLOCK_EMPTY_NAME, SPRITE_BLOCK_EMPTY_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_BOMB_NAME, SPRITE_BLOCK_BOMB_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_HIDDEN_NAME, SPRITE_BLOCK_HIDDEN_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_BOMB_SPLASH_NAME, SPRITE_BLOCK_BOMB_SPLASH_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_FLAG_NAME, SPRITE_BLOCK_FLAG_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_01_NAME, SPRITE_BLOCK_01_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_02_NAME, SPRITE_BLOCK_02_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_03_NAME, SPRITE_BLOCK_03_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_04_NAME, SPRITE_BLOCK_04_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_05_NAME, SPRITE_BLOCK_05_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_06_NAME, SPRITE_BLOCK_06_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_07_NAME, SPRITE_BLOCK_07_FILEPATH);
	this->data->assets.LoadTexture(SPRITE_BLOCK_08_NAME, SPRITE_BLOCK_08_FILEPATH);
}

void ks::GameScene::Init()
{
	this->LoadAssets();

	this->grid = new Grid(GRID_COLUMNS, GRID_ROWS, sf::Vector2i(0, 88), this->data);
	
	this->grid->Init();
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
			if (this->data->input.IsRectClicked(this->grid->GetGlobalBounds(), sf::Mouse::Left, this->data->window, event.mouseButton))
			{
				this->grid->ProcessClick(this->data->input.GetMousePosition(this->data->window));
			}

			if (this->data->input.IsRectClicked(this->grid->GetGlobalBounds(), sf::Mouse::Right, this->data->window, event.mouseButton))
			{
				this->grid->PutFlag(this->data->input.GetMousePosition(this->data->window));
			}
		}
	}
}

void ks::GameScene::Update(float deltaTime)
{
	this->grid->Update(deltaTime);
}

void ks::GameScene::Draw(float deltaTime)
{
	this->data->window.clear(sf::Color::Black);

	this->grid->Draw(deltaTime);

	this->data->window.display();
}