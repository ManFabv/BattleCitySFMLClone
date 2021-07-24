#pragma once

#include "GameEngineExportDefine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>
#include "GameEngine/ConfigLoader.h"

namespace GameEngine
{
	namespace DataUtils
	{
		class GAMEENGINE_API AssetLoader
		{
		public:
			AssetLoader(const std::string& root_folder, const std::string& textures_folder, const std::string& fonts_folder, const std::string& sounds_folder);
			~AssetLoader();
			void ChangeLookupPath(const std::string& root_folder, const std::string& textures_folder, const std::string& fonts_folder, const std::string& sounds_folder);
			const sf::Texture& GetTexture(const std::string& asset_name);
			const sf::Font& GetFont(const std::string& asset_name);
			const sf::SoundBuffer& GetSound(const std::string& asset_name);

		private:			
			const std::string GetLookupPath(const std::string& asset_folder, const std::string& asset_name);

			std::map<std::string, sf::Texture*> m_textures;
			std::map<std::string, sf::Font*> m_fonts;
			std::map<std::string, sf::SoundBuffer*> m_sounds;

			std::string m_root_folder;
			std::string m_textures_folder;
			std::string m_fonts_folder;
			std::string m_sounds_folder;
		};
	}
}
