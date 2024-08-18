#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Mouse
{
public:
	Mouse();

	// "Get" functions
	sf::Vector2f getPos() { return position; }


	// Draw all relevent features
	void draw(sf::RenderWindow& t_window);
	void update(sf::Vector2f t_bearPos);
	void returnToBear(sf::Vector2f t_position);

	// Throwing
	void throwMouse();
	sf::Vector2f target;
	bool thrown = false;
	bool returned = true;

	bool alive = true;


private:


	// Body
	sf::RectangleShape body;
	int width = 20;
	int height = 20;

	sf::Vector2f position;

	// Throwing
	float throwSpeed = 14.0f;

	// Returning
	float returnSpeed = 6.5f;

};

