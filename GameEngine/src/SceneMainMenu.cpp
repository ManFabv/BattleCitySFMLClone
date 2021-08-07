#include "GameEngine/SceneMainMenu.h"

using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::Scenes;
using namespace GameEngine::Components;
using namespace GameEngine::Systems;

void SceneMainMenu::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader)
{
	AbstractSceneBase::InitializeSystems(game_data, config_loader, asset_loader);

	entt::entity gamefont_title_entity = m_registry.create();
	entt::entity gamefont_start_entity = m_registry.create();
	LoadGameFonts(gamefont_title_entity, gamefont_start_entity, asset_loader, game_data.font_name);

	m_menu_player_input_system = new MenuCustomPlayerInputSystem();
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

	if (m_menu_player_input_system != nullptr)
	{
		delete m_menu_player_input_system;
		m_menu_player_input_system = nullptr;
	}
}

void SceneMainMenu::UpdateUI(float dt)
{
	//TODO: NOTHING SO FAR, WE SHOULD CHANGE STRUCTURE TO AVOID OVERRIDING UNNEEDED METHODS
}

void SceneMainMenu::CheckWinLoseConditions()
{
	//TODO: NOTHING SO FAR, WE SHOULD CHANGE STRUCTURE TO AVOID OVERRIDING UNNEEDED METHODS
}

void SceneMainMenu::CustomPlayerInput()
{
	m_menu_player_input_system->Execute(m_registry);
}

void SceneMainMenu::LoadGameFonts(entt::entity entity_title, entt::entity entity_start, AssetLoader& asset_loader, const std::string& file_name)
{
	m_game_title_font = new sf::Text();
	m_game_title_font->setFont(asset_loader.GetFont(file_name));
	m_game_title_font->setFillColor(sf::Color::White); //TODO: style should be loaded from config file
	m_game_title_font->setCharacterSize(64); //TODO: style should be loaded from config file
	m_game_title_font->setPosition(56, 128); //TODO: score should be at the top center
	m_game_title_font->setString("BATTLE CITY SFML CLONE");
	m_registry.emplace<DrawableFontComponent>(entity_title, *m_game_title_font);

	m_start_game_font = new sf::Text();
	m_start_game_font->setFont(asset_loader.GetFont(file_name));
	m_start_game_font->setFillColor(sf::Color::White); //TODO: style should be loaded from config file
	m_start_game_font->setCharacterSize(32); //TODO: style should be loaded from config file
	m_start_game_font->setPosition(200, 610); //TODO: score should be at the top center
	m_start_game_font->setString("PRESS ENTER TO BEGIN PLAY...");
	m_registry.emplace<DrawableFontComponent>(entity_start, *m_start_game_font);
}
