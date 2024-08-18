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
	sf::Vector2f getCameraPos() { return camTarget; }

	// Draw all relevent features
	void draw(sf::RenderWindow& t_window);

	// Movement
	void checkDirection();

	bool alive = true;

private:
	// Equations
	float normalize(float value, float min, float max) { return (value - min) / (max - min); }
	float pythagoras(int a, int b) { return sqrt((a * a) + (b * b)); }

	// Body
	sf::RectangleShape body;
	int width = 50;
	int height = 100;

	// Movement
	void move();

	sf::Vector2f position = { 100, 100 };;
	Direction direction;
	const int SPEED = 10;

	// Camera info needed
	sf::Vector2f camTarget;
	const int CAM_CHANGE = 100;
	const int CAM_SPEED = 7;
};

