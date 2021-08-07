#include "GameEngine/SceneMainMenu.h"

using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::Scenes;
using namespace GameEngine::Components;

void SceneMainMenu::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader)
{
	AbstractSceneBase::InitializeSystems(game_data, config_loader, asset_loader);

	entt::entity gamefont_entity = m_registry.create();
	LoadGameFonts(gamefont_entity, asset_loader, game_data.font_name);
}

void SceneMainMenu::CleanUpSystems()
{
	AbstractSceneBase::CleanUpSystems();

	if (m_game_title_font != nullptr)
	{
		delete m_game_title_font;
		m_game_title_font = nullptr;
	}

	if (m_start_game_font != nullptr)
	{
		delete m_start_game_font;
		m_start_game_font = nullptr;
	}
}

void SceneMainMenu::UpdateUI(float dt)
{
}

void SceneMainMenu::CheckWinLoseConditions()
{
}

void SceneMainMenu::CustomPlayerInput()
{
}

void SceneMainMenu::LoadGameFonts(entt::entity entity, AssetLoader& asset_loader, const std::string& file_name)
{
	m_game_title_font = new sf::Text();
	m_game_title_font->setFont(asset_loader.GetFont(file_name));
	m_game_title_font->setFillColor(sf::Color::White); //TODO: style should be loaded from config file
	m_game_title_font->setCharacterSize(64); //TODO: style should be loaded from config file
	m_game_title_font->setPosition(56, 8); //TODO: score should be at the top center
	m_game_title_font->setString("BATTLE CITY SFML CLONE");
	m_registry.emplace<DrawableFontComponent>(entity, *m_game_title_font);
}
