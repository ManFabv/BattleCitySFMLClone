#include "GameEngine/GameManager.h"
#include "GameEngine/GameComponents.h"
#include "GameEngine/AssetLoader.h"
#include <rapidjson/document.h>

using namespace GameEngine::GameManagerMain;
using namespace GameplayUtilities::Scores;
using namespace GameEngine::Systems;
using namespace GameEngine::Components;
using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;

void GameManager::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader)
{
	world_scale.x = game_data.world_scale;
	world_scale.y = game_data.world_scale;

	std::string player_json = config_loader.LoadDataFrom(game_data.config_root_folder, game_data.animations_folder, game_data.player_config);
	
	rapidjson::Document player_json_document;
	player_json_document.Parse(player_json.c_str());

	std::string player_atlas_name = player_json_document["atlas_name"].GetString();
	entt::entity player_entity = LoadDrawableEntity(asset_loader, player_atlas_name);

	AnimationData player_anim_data;
	player_anim_data.row_index = player_json_document["anim_row"].GetInt();
	player_anim_data.horizontal_sprites = player_json_document["horizontal_sprites"].GetInt();
	player_anim_data.vertical_sprites = player_json_document["vertical_sprites"].GetInt();
	player_anim_data.sprites_width = player_json_document["sprites_width"].GetInt();
	player_anim_data.sprites_height = player_json_document["sprites_height"].GetInt();
	player_anim_data.frame_time = player_json_document["frame_time"].GetFloat();
	player_anim_data.initial_animation = player_json_document["initial_animation"].GetString();
	player_anim_data.animations_loop = player_json_document["animations_loop"].GetBool();
	//TODO: player_json_document["animations"] should be loaded from config
	LoadAnimationInformationForEntity(player_entity, player_anim_data);
	LoadMovementForEntity(player_entity);
	
	m_window = new sf::RenderWindow(sf::VideoMode(game_data.resX, game_data.resY), game_data.window_title);

	m_render_system = new RenderSystem(*m_window);
	m_anim_system = new AnimationSystem();
	m_movement_system = new MovementSystem();
}

void GameManager::RunGameLoop()
{
	sf::Clock game_clock;
	sf::Time delta_time;
	m_is_paused = false;

	while (m_window->isOpen())
	{
		delta_time = game_clock.restart();
		TakePlayerInput();
		UpdateEntities(delta_time.asMilliseconds());
		UpdateGUI();
		DrawEntities();
		DrawGUI();
	}
}

void GameManager::CleanUpSystems()
{
	m_registry.clear();

	delete m_window;
	delete m_render_system;
	delete m_anim_system;
	delete m_movement_system;
}

void GameManager::PauseGame(bool pause)
{
	m_is_paused = pause;
}

void GameManager::TakePlayerInput()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_window->close();

	if (m_is_paused)
		return;

	//TODO: add input below
}

void GameManager::UpdateEntities(float dt)
{
	if (m_is_paused)
		return;

	//TODO: implement below
	m_anim_system->Execute(m_registry, dt);
	m_movement_system->Execute(m_registry, dt);
}

void GameManager::DrawEntities()
{
	m_window->clear();

	m_render_system->Execute(m_registry);

	m_window->display();
}

void GameManager::UpdateGUI()
{
	//TODO: implement 
}

void GameManager::DrawGUI()
{
	//TODO: implement 
}

entt::entity GameManager::LoadDrawableEntity(AssetLoader& asset_loader, const std::string& file_name)
{
	entt::entity entity = m_registry.create();

	sf::Sprite* m_player_sprite = new sf::Sprite();
	m_player_sprite->setTexture(asset_loader.GetTexture(file_name));
	m_player_sprite->setScale(sf::Vector2f(m_player_sprite->getScale().x * world_scale.x, m_player_sprite->getScale().y * world_scale.y));
	m_player_sprite->setPosition(160, 704); //TODO: player should be at the spawn point position
	m_registry.emplace<DrawableComponent>(entity, *m_player_sprite);

	return entity;
}

void GameManager::LoadAnimationInformationForEntity(entt::entity entity, const AnimationData& anim_data)
{
	AnimationComponent* anim_component = new AnimationComponent();
	anim_component->m_frames.push_back(sf::IntRect(0, 0, 16, 16));
	anim_component->m_frames.push_back(sf::IntRect(16, 0, 16, 16));
	anim_component->m_loop = true;
	anim_component->m_duration = 0.2f;
	m_registry.emplace<AnimationComponent>(entity, *anim_component);
}

void GameManager::LoadMovementForEntity(entt::entity entity)
{
	MovementComponent* movement_component = new MovementComponent();
	movement_component->m_velocity = sf::Vector2f(0, -1); //TODO: velocity should be taken from player config file
	m_registry.emplace<MovementComponent>(entity, *movement_component);
}
