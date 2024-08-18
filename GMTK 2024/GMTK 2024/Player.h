#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Mouse.h"

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
	void update(sf::Vector2f t_mousePos);

	// Movement
	void checkDirection();

	bool alive = true;

	// Throwing Mouse
	Mouse mouse;
	void throwMouse(sf::Vector2f t_target);

	bool aiming = false;

private:

	// Shader
	sf::Shader shadow;

	// Body
	sf::RectangleShape body;
	int width = 50;
	int height = 100;

	// Movement
	void move();

	sf::Vector2f position = { 100, 100 };;
	Direction direction;
	const int SPEED = 5;

	// Camera info needed
	sf::Vector2f camTarget;
	const int CAM_CHANGE = 100;

	// Throwing Mouse
	void aim(sf::Vector2f t_mousePos);
	sf::CircleShape crosshair;

	// Mouse info while held
	sf::Vector2f mouseHeldPos;
};

