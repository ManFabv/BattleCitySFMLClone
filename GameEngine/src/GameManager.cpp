#include "GameEngine/GameManager.h"
#include <SFML/Graphics.hpp>
#include "GameplayUtilities/ScoreManager.h"
#include "entt/entt.hpp"

using namespace GameEngine::GameManagerMain;
using namespace GameplayUtilities::ScoreManager;

GameManager::GameManager()
{
}

void GameManager::TestGameEngineImplementation()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    ScoreManager score_manager;
    score_manager.ScoresCount();
    entt::registry registry;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
