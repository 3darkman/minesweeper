#include "AssetManager.h"

void ks::AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;

	if (tex.loadFromFile(fileName))
	{
		this->textures.insert(std::pair<std::string, sf::Texture>(name, tex));
	}
}

sf::Texture& ks::AssetManager::GetTexture(std::string name)
{
	return this->textures.at(name);
}

void ks::AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		this->fonts.insert(std::pair<std::string, sf::Font>(name, font));
	}
}

sf::Font& ks::AssetManager::GetFont(std::string name)
{
	return this->fonts.at(name);
}