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

	void processEvents(sf::Event t_event, sf::RenderWindow &t_window);
	void processMouseDown(sf::Event t_event, sf::RenderWindow& t_window);
	void processMouseMove(sf::Event t_event);


	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	sf::Vector2f mousePos;

	sf::Texture tilesTexture;
	sf::Sprite tilesSprite;
	
	// Buttons
	void setupButtons();

	sf::Font font;
	sf::Text gameplayText;
	sf::Text exitText;

	Button gameplayButton;
	bool gameplayColliding = false;

	Button exitGameButton;
	bool exitGameButtonColliding = false;

};