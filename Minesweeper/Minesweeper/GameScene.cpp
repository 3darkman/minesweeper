#include "GameScene.h"
#include "DEFINITIONS.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"

ks::GameScene::GameScene(GameDataRef data) : data(data)
{
	this->hintText = nullptr;
	this->victoryText = nullptr;
	this->canClickToRestart = false;
	this->state = GameState::Running;
	switch (this->data->difficult)
	{
	case GameDifficult::Intermediate:
		this->data->window.create(sf::VideoMode(INTERMEDIATE_SCREEN_WIDTH, INTERMEDIATE_SCREEN_HEIGHT), this->data->title, sf::Style::Close | sf::Style::Titlebar);
		break;
	case GameDifficult::Beginner:
		this->data->window.create(sf::VideoMode(BEGINNER_SCREEN_WIDTH, BEGINNER_SCREEN_HEIGHT), this->data->title, sf::Style::Close | sf::Style::Titlebar);
		break;
	case GameDifficult::Expert:
		this->data->window.create(sf::VideoMode(EXPERT_SCREEN_WIDTH, EXPERT_SCREEN_HEIGHT), this->data->title, sf::Style::Close | sf::Style::Titlebar);
		break;
	}
	this->data->window.setFramerateLimit(DEFAULT_FRAME_RATE);
}

ks::GameScene::~GameScene()
{
	delete this->grid;
	delete this->victoryText;
	delete this->hintText;
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
	this->data->assets.LoadTexture(SPRITE_LOGO_NAME, SPRITE_LOGO_FILEPATH);
	this->data->assets.LoadFont(FONT_GAME_SANS_NAME, FONT_GAME_SANS_FILEPATH);
	
}

void ks::GameScene::CreateGrid()
{
	switch (this->data->difficult)
	{
	case GameDifficult::Intermediate:
		this->grid = new Grid(INTERMEDIATE_GRID_COLUMNS, INTERMEDIATE_GRID_ROWS, sf::Vector2i(0, 88), this->data);
		break;
	case GameDifficult::Beginner:
		this->grid = new Grid(BEGINNER_GRID_COLUMNS, BEGINNER_GRID_ROWS, sf::Vector2i(0, 88), this->data);
		break;
	case GameDifficult::Expert:
		this->grid = new Grid(EXPERT_GRID_COLUMNS, EXPERT_GRID_ROWS, sf::Vector2i(0, 88), this->data);
		break;
	}
	this->grid->Init();
}

void ks::GameScene::Init()
{
	this->LoadAssets();
	state = GameState::Running;

	this->logo.setTexture(this->data->assets.GetTexture(SPRITE_LOGO_NAME));
	this->logo.setScale(0.35f, 0.35f);
	this->AnchorObject(this->data->window, this->logo, this->logo.getGlobalBounds(), AnchorType::TopRight, sf::Vector2i(-5, 5));

	this->CreateGrid();

	this->victoryText = new sf::Text("You Won!", this->data->assets.GetFont(FONT_GAME_SANS_NAME), 25);
	this->AnchorObject(this->data->window, *this->victoryText, this->victoryText->getLocalBounds(), AnchorType::TopLeft, sf::Vector2i(5, 20));

	this->hintText = new sf::Text("press <Enter>", this->data->assets.GetFont(FONT_GAME_SANS_NAME), 10);
	this->AnchorObject(this->data->window, *this->hintText, this->hintText->getLocalBounds(), AnchorType::TopLeft, sf::Vector2i(5, 60));
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
		if (this->grid->GetRevealedBlocks() >= ((this->grid->GetSize().x * this->grid->GetSize().y) - this->grid->GetNumberOfBombs()))
		{
			this->clock.restart();
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
		
		if (this->state == GameState::Running)
		{
			if (event.type == sf::Event::MouseButtonPressed)
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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					this->data->scenes.AddScene(SceneRef(new GameScene(this->data)), true);
				}
			}
		}

		if (this->state == GameState::Won)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					this->data->scenes.AddScene(SceneRef(new MainMenuScene(this->data)), true);
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && canClickToRestart)
			{
				this->data->scenes.AddScene(SceneRef(new MainMenuScene(this->data)), true);
			}
		}
	}
}

void ks::GameScene::Update(float deltaTime)
{
	if (this->state != GameState::Running)
	{
		if(this->clock.getElapsedTime().asSeconds() >= PAUSE_TIME_AFTER_GAME_END)
		{
			if (this->state == GameState::Lose)
			{
				this->data->scenes.AddScene(SceneRef(new GameOverScene(this->data)), true);
			}
			if (this->state == GameState::Won)
			{
				canClickToRestart = true;
			}
		}
	}
	
}

void ks::GameScene::Draw(float deltaTime)
{
	this->data->window.clear(sf::Color(45,43,43));

	this->grid->Draw(deltaTime);
	
	this->data->window.draw(this->logo);

	if (this->state == GameState::Won)
	{
		
		this->data->window.draw(*this->victoryText);
		this->data->window.draw(*this->hintText);
	}

	this->data->window.display();
}