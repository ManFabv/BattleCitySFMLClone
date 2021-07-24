#include "GameEngine/GameManager.h"
#include "GameEngine/GameComponents.h"
#include <rapidjson/document.h>
#include "GameEngine/AssetLoader.h"

using namespace GameEngine::GameManagerMain;
using namespace GameplayUtilities::Scores;
using namespace GameEngine::Systems;
using namespace GameEngine::Components;
using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;

void GameManager::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader)
{
	std::string player_json = config_loader.LoadDataFrom(game_data.config_root_folder, game_data.animations_folder, game_data.player_config);
	
	rapidjson::Document player_json_document;
	player_json_document.Parse(player_json.c_str());

	std::string player_atlas_name = player_json_document["atlas_name"].GetString();
	LoadDrawableEntity(asset_loader, game_data.config_root_folder, game_data.textures_folder, player_atlas_name);
	
	m_window = new sf::RenderWindow(sf::VideoMode(game_data.resX, game_data.resY), game_data.window_title);

	m_render_system = new RenderSystem(*m_window);
}

void GameManager::RunGameLoop()
{
	sf::Clock game_clock;
	sf::Time delta_time;

	while (m_window->isOpen())
	{
		delta_time = game_clock.restart();
		TakePlayerInput();
		UpdateEntities(delta_time.asMilliseconds());
		DrawEntities();
	}
}

void GameManager::CleanUpSystems()
{
	m_registry.clear();

	delete m_window;
	delete m_render_system;
}

void GameManager::TakePlayerInput()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
	}
}

void GameManager::UpdateEntities(float dt)
{
	//TODO: implement
}

void GameManager::DrawEntities()
{
	m_window->clear();

	m_render_system->Execute(m_registry);

	m_window->display();
}

void GameManager::LoadDrawableEntity(AssetLoader& asset_loader, const std::string& root_folder, const std::string& config_folder, const std::string& file_name)
{
	entt::entity entity = m_registry.create();

	sf::Sprite* m_player_sprite = new sf::Sprite();
	m_player_sprite->setTexture(asset_loader.GetTexture(file_name));

	m_registry.emplace<DrawableComponent>(entity, *m_player_sprite);
}
