#pragma once

#include "GameEngineExportDefine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <map>
#include "GameEngine/ConfigLoader.h"

namespace GameEngine
{
	namespace DataUtils
	{
		class GAMEENGINE_API AssetLoader
		{
		public:
			~AssetLoader();
			void LoadTexture(const entt::entity entity_id, const std::string& root_folder, const std::string& config_folder, const std::string& file_name);
			const sf::Texture& GetTexture(const entt::entity entity_id);
		private:
			std::map<entt::entity, sf::Texture*> m_textures;
		};
	}
}
