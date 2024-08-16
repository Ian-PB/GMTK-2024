#include "Pause.h"

Pause::Pause()
{

}

void Pause::processEvents(sf::Event t_event)
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

void Pause::processMouseDown(sf::Event t_event)
{

}

void Pause::processMouseMove(sf::Event t_event)
{
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}


void Pause::update(sf::Time t_deltaTime)
{

}

void Pause::render(sf::RenderWindow& t_window)
{

}