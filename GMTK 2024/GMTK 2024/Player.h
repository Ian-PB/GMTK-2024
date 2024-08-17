#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Player
{
public:

	Player();

	// "Get" functions
	sf::Vector2f getPos() { return position; }
	sf::Vector2f getCameraPos() { return camPos; }

	// Draw all relevent features
	void draw(sf::RenderWindow& t_window);

	// Movement
	void checkDirection();

private:

	// Body
	sf::RectangleShape body;
	int width = 50;
	int height = 100;

	// Movement
	void move();
	void updateCam();

	sf::Vector2f position;
	Direction direction;
	int speed = 10;

	// Camera info needed
	sf::Vector2f camPos;
	const int CAM_CHANGE = 50;
};

