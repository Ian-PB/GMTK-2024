#include "SplashScreen.h"


SplashScreen::SplashScreen()
{

}

void SplashScreen::processEvents(sf::Event t_event)
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

void SplashScreen::processMouseDown(sf::Event t_event)
{

}

void SplashScreen::processMouseMove(sf::Event t_event)
{
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}


void SplashScreen::update(sf::Time t_deltaTime)
{

}

void SplashScreen::render(sf::RenderWindow& t_window)
{

}