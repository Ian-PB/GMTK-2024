#include "GamePlay.h"


GamePlay::GamePlay()
{

}

void GamePlay::processEvents(sf::Event t_event)
{
	// Mouse
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}

	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
	}
}

void GamePlay::processMouseDown(sf::Event t_event)
{

}

void GamePlay::processMouseMove(sf::Event t_event)
{
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}


void GamePlay::update(sf::Time t_deltaTime)
{

}

void GamePlay::render(sf::RenderWindow& t_window)
{

}