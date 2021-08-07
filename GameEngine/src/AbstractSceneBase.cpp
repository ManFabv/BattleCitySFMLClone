#include "GameEngine/AbstractSceneBase.h"

using namespace GameEngine::Scenes;

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
	m_registry.clear();

	delete m_window;
	delete m_render_system;
	delete m_anim_system;
	delete m_movement_system;
	delete m_rendergui_system;
	delete m_input_system;
	delete m_playeranimatorcontroller_system;
	delete m_dynamic_collider_system;
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
