#include "GameEngine/AssetLoader.h"
#include "GameEngine/FilePathHelper.h"

using namespace GameEngine::DataUtils;

AssetLoader::AssetLoader(const std::string& root_folder, const std::string& config_folder)
{
	ChangeLookupPath(root_folder, config_folder);
}

AssetLoader::~AssetLoader()
{
	m_assets.clear();
}

void AssetLoader::ChangeLookupPath(const std::string& root_folder, const std::string& config_folder)
{
	m_root_folder = root_folder;
	m_config_folder = config_folder;
}

const sf::Texture& AssetLoader::GetAsset(const std::string& asset_name)
{
	std::map<std::string, sf::Texture*>::iterator asset_found = m_assets.find(asset_name);

	if (asset_found != m_assets.end())
	{
		return (*asset_found->second);
	}
	else
	{
		sf::Texture* asset = new sf::Texture();
		asset->loadFromFile(GetLookupPath(asset_name));
		m_assets[asset_name] = asset;
		return *asset;
	}
}

const std::string AssetLoader::GetLookupPath(const std::string& asset_name)
{
	return FilePathHelper::GeneratePath(m_root_folder, m_config_folder, asset_name);
}
