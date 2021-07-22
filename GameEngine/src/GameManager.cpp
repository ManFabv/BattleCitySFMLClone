#include "GameEngine/GameManager.h"
#include "GameEngine/GameComponents.h"
#include <rapidjson/document.h>

using namespace GameEngine::GameManagerMain;
using namespace GameplayUtilities::Scores;
using namespace GameEngine::Systems;
using namespace GameEngine::Components;
using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;

void GameManager::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader)
{
	std::string player_json = config_loader.LoadDataFrom(game_data.config_root_folder, game_data.animations_folder, game_data.player_config);
	
	rapidjson::Document player_json_document;
	player_json_document.Parse(player_json.c_str());

	std::string player_atlas_name = player_json_document["atlas_name"].GetString();
	std::string player_atlas_path = config_loader.GeneratePath(game_data.config_root_folder, game_data.textures_folder, player_atlas_name);
	m_player_texture.loadFromFile(player_atlas_path);
	m_player_sprite.setTexture(m_player_texture);
	entt::entity player_entity = m_registry.create();
	m_registry.emplace<DrawableComponent>(player_entity, m_player_sprite);
	
	m_window = new sf::RenderWindow(sf::VideoMode(game_data.resX, game_data.resY), game_data.window_title);

	m_render_system = new RenderSystem(*m_window);
}

void GameManager::RunGameLoop()
{
	while (m_window->isOpen())
	{
		TakePlayerInput();
		UpdateEntities();
		DrawEntities();
	}
}

void GameEngine::GameManagerMain::GameManager::CleanUpSystems()
{
	m_registry.clear();

	delete m_window;
	delete m_render_system;
}

void GameEngine::GameManagerMain::GameManager::TakePlayerInput()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
	}
}

void GameEngine::GameManagerMain::GameManager::UpdateEntities()
{
	//TODO: implement
}

void GameEngine::GameManagerMain::GameManager::DrawEntities()
{
	m_window->clear();

	m_render_system->Execute(m_registry);

	m_window->display();
}
