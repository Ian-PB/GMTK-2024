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
	void throwSelf(sf::Vector2f t_initialPos, sf::Vector2f t_target);
	void throwMovement();
	sf::Vector2f target;
	bool thrown = false;
	bool returned = false;

	bool alive = true;


private:


	// Body
	sf::RectangleShape body;
	float scale = 1.0f;
	int width = 20;
	int height = 20;

	sf::Vector2f position;

	// Throwing
	sf::Vector2f positionThrownFrom;
	float throwSpeed = 14.0f;
	float arcHeight = -10.0f;

	// Returning
	float returnSpeed = 6.5f;

};

