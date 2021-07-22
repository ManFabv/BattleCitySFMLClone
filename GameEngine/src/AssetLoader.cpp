#include "GameEngine/AssetLoader.h"
#include "GameEngine/FilePathHelper.h"

using namespace GameEngine::DataUtils;

GameEngine::DataUtils::AssetLoader::~AssetLoader()
{
	//for (auto texture : m_textures)
	//	delete texture->second;

	m_textures.clear();
}

void GameEngine::DataUtils::AssetLoader::LoadTexture(const entt::entity entity_id, const std::string& root_folder, const std::string& config_folder, const std::string& file_name)
{
	sf::Texture *texture = new sf::Texture();
	std::string texture_name = FilePathHelper::GeneratePath(root_folder, config_folder, file_name);
	texture->loadFromFile(texture_name);
	m_textures.insert(std::pair(entity_id, texture));
}

const sf::Texture& GameEngine::DataUtils::AssetLoader::GetTexture(const entt::entity entity_id)
{
	return *m_textures[entity_id];
}
