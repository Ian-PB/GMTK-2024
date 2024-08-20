#pragma once

#include <SFML/Graphics.hpp>
#include "Scenes.h"

class Button
{
public:


	sf::RectangleShape getBody() { return body; }

	void setup(sf::Vector2f t_pos, float t_width, float t_height, Scene t_sendTo, sf::Color t_color);

	bool checkForMouse(sf::Vector2f t_mousePos);

	Scene sendTo = Scene::None;

private:

	sf::RectangleShape body;
	float width;
	float height;

	sf::Vector2f position;

	bool colliding = false;

};