#include "GameEngine/AssetLoader.h"
#include "GameEngine/FilePathHelper.h"

using namespace GameEngine::DataUtils;

AssetLoader::AssetLoader(const std::string& root_folder, const std::string& textures_folder, const std::string& fonts_folder, const std::string& sounds_folder)
{
	ChangeLookupPath(root_folder, textures_folder, fonts_folder, sounds_folder);
}

AssetLoader::~AssetLoader()
{
	m_textures.clear();
	m_fonts.clear();
	m_sounds.clear();
}

void AssetLoader::ChangeLookupPath(const std::string& root_folder, const std::string& textures_folder, const std::string& fonts_folder, const std::string& sounds_folder)
{
	m_root_folder = root_folder;
	m_textures_folder = textures_folder;
	m_fonts_folder = fonts_folder;
	m_sounds_folder = sounds_folder;
}

const sf::Texture& AssetLoader::GetTexture(const std::string& asset_name)
{
	std::map<std::string, sf::Texture*>::iterator asset_found = m_textures.find(asset_name);

	if (asset_found != m_textures.end())
	{
		return (*asset_found->second);
	}
	else
	{
		sf::Texture* asset = new sf::Texture();
		asset->loadFromFile(GetLookupPath(m_textures_folder, asset_name));
		m_textures[asset_name] = asset;
		return *asset;
	}
}

const sf::Font& AssetLoader::GetFont(const std::string& asset_name)
{
	std::map<std::string, sf::Font*>::iterator asset_found = m_fonts.find(asset_name);

	if (asset_found != m_fonts.end())
	{
		return (*asset_found->second);
	}
	else
	{
		sf::Font* asset = new sf::Font();
		asset->loadFromFile(GetLookupPath(m_fonts_folder, asset_name));
		m_fonts[asset_name] = asset;
		return *asset;
	}
}

const sf::SoundBuffer& AssetLoader::GetSound(const std::string& asset_name)
{
	std::map<std::string, sf::SoundBuffer*>::iterator asset_found = m_sounds.find(asset_name);

	if (asset_found != m_sounds.end())
	{
		return (*asset_found->second);
	}
	else
	{
		sf::SoundBuffer* asset = new sf::SoundBuffer();
		asset->loadFromFile(GetLookupPath(m_sounds_folder, asset_name));
		m_sounds[asset_name] = asset;
		return *asset;
	}
}

const std::string AssetLoader::GetLookupPath(const std::string& asset_folder, const std::string& asset_name)
{
	return FilePathHelper::GeneratePath(m_root_folder, asset_folder, asset_name);
}
