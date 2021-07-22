#include "GameEngine/GameManager.h"
#include "GameEngine/GameComponents.h"
#include "GameplayUtilities/File.h"
#include <rapidjson/document.h>




#include <iostream>



using namespace GameEngine::GameManagerMain;
using namespace GameplayUtilities::Scores;
using namespace GameEngine::Systems;
using namespace GameEngine::Components;
using namespace GameplayUtilities::IO;

void GameManager::InitializeSystems(const int resX, const int resY, const char* window_title, const char* config_folder)
{
	std::string player_anim_file = config_folder;
	player_anim_file += "\\animations\\player_anim.json";
	File file_reader;
	file_reader.OpenForRead(player_anim_file);
	rapidjson::Document json_document;
	json_document.Parse(file_reader.Read().c_str());
	if(json_document.HasMember("sprites_width"))
		std::cout << "HAS MEMBER";
	m_window = new sf::RenderWindow(sf::VideoMode(resX, resY), window_title);

	m_render_system = new RenderSystem(*m_window);
}

void GameManager::RunGameLoop()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(sf::Vector2f(100.f, 250.f));

	sf::CircleShape shape2(100.f);
	shape2.setFillColor(sf::Color::Magenta);
	shape2.setPosition(sf::Vector2f(500.f, 250.f));

	entt::entity entity = m_registry.create();
	m_registry.emplace<DrawableComponent>(entity, shape);

	entt::entity entity2 = m_registry.create();
	m_registry.emplace<DrawableComponent>(entity2, shape2);

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
}

void GameEngine::GameManagerMain::GameManager::DrawEntities()
{
	m_window->clear();

	m_render_system->Execute(m_registry);

	m_window->display();
}
