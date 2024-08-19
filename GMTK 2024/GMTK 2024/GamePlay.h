#pragma once

# include <SFML/Graphics.hpp>

#include "Scenes.h"
#include "Globals.h"

#include "Player.h"
#include "Mouse.h"
#include "Enemy.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"


class Game;

class GamePlay
{
public:
	GamePlay();

	void processEvents(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);
	void processMouseMove(sf::RenderWindow& t_window);

	void setupUI();

	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);

private:

	void updateCamera();

	// Font
	sf::Font font;
	sf::Text healthText;
	
	// Player Object
	Player benjamin;

	sf::Vector2f mousePos;

	// View
	sf::View camera;
	sf::Vector2f camPos;
	float camSpeed = 0;

	// Sprites
	sf::Sprite tilesSprite;
	sf::Texture tilesTexture;


	// Enemies
	MeleeEnemy meleeEnemies[10];

	// Equations
	sf::Vector2f vectorBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return (t_b - t_a); }
	float angleBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return atan2(t_b.y - t_a.y, t_b.x - t_a.x) * (180 / PI); }
	float vectorLenght(sf::Vector2f t_a, sf::Vector2f t_b) { return (sqrt((t_b.x - t_a.x) * (t_b.x - t_a.x) + (t_b.y - t_a.y) * (t_b.y - t_a.y))); }
	sf::Vector2f scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance);
};