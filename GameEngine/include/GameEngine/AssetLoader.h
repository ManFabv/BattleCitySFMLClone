#pragma once

#include "GameEngineExportDefine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
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
			AssetLoader(const std::string& root_folder, const std::string& config_folder);
			~AssetLoader();
			void ChangeLookupPath(const std::string& root_folder, const std::string& config_folder);
			const sf::Texture& GetAsset(const std::string& asset_name);
		private:
			const std::string GetLookupPath(const std::string& asset_name);

			std::map<std::string, sf::Texture*> m_assets;

			std::string m_root_folder;
			std::string m_config_folder;
		};
	}
}
