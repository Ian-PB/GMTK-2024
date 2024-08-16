#pragma once

# include <SFML/Graphics.hpp>

#include "Scenes.h"


class Game;

class SplashScreen
{
public:
	SplashScreen();

	void processEvents(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseMove(sf::Event t_event);


	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	sf::Vector2f mousePos;


};