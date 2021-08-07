#include "GameEngine/AbstractSceneBase.h"

using namespace GameEngine::Scenes;
using namespace GameEngine::Systems;

void AbstractSceneBase::InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader)
{
	SetupCommonSystems(game_data.resX, game_data.resY, game_data.window_title);
}

void AbstractSceneBase::RunGameLoop()
{
	sf::Clock game_clock;
	sf::Time delta_time;
	m_is_paused = false;

	while (m_window->isOpen())
	{
		delta_time = game_clock.restart();
		TakePlayerInput();
		UpdateEntities(delta_time.asSeconds());
		UpdatePhysics();
		UpdateUI(delta_time.asSeconds());
		DrawEntities();
		CheckWinLoseConditions();
	}
}

void AbstractSceneBase::CleanUpSystems()
{
	CleanupCommonSystems();
}

void AbstractSceneBase::PauseGame(bool pause)
{
	m_is_paused = pause;
}

void AbstractSceneBase::TakePlayerInput()
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
	CustomPlayerInput();
}

void AbstractSceneBase::UpdateEntities(float dt)
{
	if (m_is_paused)
		return;

	//TODO: implement below
	m_playeranimatorcontroller_system->Execute(m_registry, dt);
	m_anim_system->Execute(m_registry, dt);
	m_movement_system->Execute(m_registry, dt);
}

void AbstractSceneBase::UpdatePhysics()
{
	m_dynamic_collider_system->Execute(m_registry);
}

void AbstractSceneBase::DrawEntities()
{
	m_window->clear();

	m_render_system->Execute(m_registry);

	m_rendergui_system->Execute(m_registry);

	m_window->display();
}

void AbstractSceneBase::SetupCommonSystems(int resX, int resY, const std::string& window_title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(resX, resY), window_title);
	m_window->setVerticalSyncEnabled(true);

	m_render_system = new RenderSystem(*m_window);
	m_rendergui_system = new RenderGUISystem(*m_window);
	m_anim_system = new AnimationSystem();
	m_movement_system = new MovementSystem();
	m_input_system = new InputSystem();
	m_playeranimatorcontroller_system = new PlayerAnimatorControllerSystem();
	m_dynamic_collider_system = new DynamicColliderSystem();
}

void AbstractSceneBase::CleanupCommonSystems()
{
	m_registry.clear();

	if(m_window != nullptr)
	{
		delete m_window;
		m_window = nullptr;
	}
	if (m_render_system != nullptr)
	{	
		delete m_render_system;
		m_render_system = nullptr;
	}
	if (m_anim_system != nullptr)
	{	
		delete m_anim_system;
		m_anim_system = nullptr;
	}
	if (m_movement_system != nullptr)
	{	
		delete m_movement_system;
		m_movement_system = nullptr;
	}
	if (m_rendergui_system != nullptr)
	{	
		delete m_rendergui_system;
		m_rendergui_system = nullptr;
	}
	if (m_input_system != nullptr)
	{	
		delete m_input_system;
		m_input_system = nullptr;
	}
	if (m_playeranimatorcontroller_system != nullptr)
	{	
		delete m_playeranimatorcontroller_system;
		m_playeranimatorcontroller_system = nullptr;
	}
	if (m_dynamic_collider_system != nullptr)
	{
		delete m_dynamic_collider_system;
		m_dynamic_collider_system = nullptr;
	}
}
