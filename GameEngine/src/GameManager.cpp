#include "GameEngine/GameManager.h"
#include <SFML/Graphics.hpp>
#include "GameplayUtilities/ScoreManager.h"
#include "entt/entt.hpp"
#include "GameEngine/RenderSystem.h"
#include "GameEngine\GameComponents.h"

using namespace GameEngine::GameManagerMain;
using namespace GameplayUtilities::ScoreManager;
using namespace GameEngine::Systems;

GameManager::GameManager()
{
}

void GameManager::TestGameEngineImplementation()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(200.f, 250.f));
	sf::CircleShape shape2(100.f);
	shape2.setFillColor(sf::Color::Magenta);
	shape2.setPosition(sf::Vector2f(900.f, 250.f));
    
    ScoreManager score_manager;
    score_manager.ScoresCount();
    
    entt::registry registry;
    entt::entity entity = registry.create();
    registry.emplace<DrawableComponent>(entity, shape);
	entt::entity entity2 = registry.create();
	registry.emplace<DrawableComponent>(entity2, shape2);
    RenderSystem render_system(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        
        render_system.Execute(registry);
        
        window.display();
    }

    registry.clear();
}
