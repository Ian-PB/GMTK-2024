#pragma once

# include <SFML/Graphics.hpp>
# include <iostream>

#include "Scenes.h"
#include "Globals.h"
#include "Button.h"


class Game;

class MainMenu
{
public:
	MainMenu();

	void processEvents(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseMove(sf::Event t_event);


	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	sf::Vector2f mousePos;
	
	// Buttons
	void setupButtons();

	sf::Font font;
	sf::Text gameplayText;

	Button gameplayButton;
	bool gameplayColliding = false;

};