#include "Button.h"


void Button::setup(sf::Vector2f t_pos, float t_width, float t_height, Scene t_sendTo, sf::Color t_color)
{
	// Get the scene it should send you to
	sendTo = t_sendTo;

	// Get the dimensions
	width = t_width;
	height = t_height;


	body.setSize({ width, height });
	body.setFillColor(t_color);

	body.setOrigin({ width / 2, height / 2 });

	position = t_pos;
	body.setPosition(position);
}

bool Button::checkForMouse(sf::Vector2f t_mousePos)
{
	// Check if the mouse is within the button on the x-axis
	if (t_mousePos.x >= position.x - ((width) / 2) && t_mousePos.x <= position.x + ((width) / 2))
	{
		// Check if the mouse is within the button on the y-axis
		if (t_mousePos.y <= position.y + (height / 2) && t_mousePos.y >= position.y - (height / 2))
		{
			// if colliding
			colliding = true;
			return colliding;
		}
	}

	// if not colliding 
	colliding = false;

	return colliding; // if not colliding
}