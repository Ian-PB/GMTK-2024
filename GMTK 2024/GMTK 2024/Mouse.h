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

	bool alive = true;

private:

	// Body
	sf::RectangleShape body;
	int width = 20;
	int height = 20;

	sf::Vector2f position;

};

