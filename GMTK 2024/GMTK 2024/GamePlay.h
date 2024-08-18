#pragma once

# include <SFML/Graphics.hpp>

#include "Scenes.h"
#include "Globals.h"

#include "Player.h"
#include "Mouse.h"


class Game;

class GamePlay
{
public:
	GamePlay();

	void processEvents(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseMove(sf::Event t_event);


	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	void updateCamera();

	
	// Player Object
	Player benjamin;
	Mouse mouse;

	sf::Vector2f mousePos;

	// View
	sf::View camera;
	sf::Vector2f camPos;
	float camSpeed = 10;

	// Sprites
	sf::Sprite tilesSprite;
	sf::Texture tilesTexture;


};