#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace ks
{
	/**
	 * Implementation of a management class of external assets.
	 *
	 * It allows you to load the necessary assets at a given time, and keeps them stored
	 * for later use.
	 */
	class AssetManager
	{
	public:
		AssetManager() {}
		~AssetManager() {}

		/**
		 * Load texture from file and keep it stored for later use
		 *
		 * @param name Name by which the texture will be identified in the texture library
		 * @param fileName name and location of the file from which the texture will be loaded
		 */
		void LoadTexture(std::string name, std::string fileName);

		/**
		 * Get a texture previously loaded into the library
		 *
		 * @param name Identification of the texture in the library, the same name that was
		 * used when loading it to the library must be used.
		 * @return if it exists in the library, it returns the texture, otherwise it returns
		 * an empty pointer.
		 */
		sf::Texture& GetTexture(std::string name);

		/**
		 * Load Font from file and keep it stored for later use
		 *
		 * @param name Name by which the font will be identified in the font library
		 * @param fileName name and location of the file from which the font will be loaded
		 */
		void LoadFont(std::string name, std::string fileName);

		/**
		 * Get a font previously loaded into the library
		 *
		 * @param name Identification of the font in the library, the same name that was
		 * used when loading it to the library must be used.
		 * @return if it exists in the library, it returns the font, otherwise it returns
		 * an empty pointer.
		 */
		sf::Font& GetFont(std::string name);

	private:
		/// map of loaded textures, indexed by the name provided when loading them.
		std::map<std::string, sf::Texture> textures;
		
		/// map of loaded fonts, indexed by the name provided when loading them.
		std::map<std::string, sf::Font> fonts;
	};
}