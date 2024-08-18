#include "Mouse.h"

Mouse::Mouse()
{
	// Setup body
	body.setFillColor(sf::Color::Blue);
	body.setSize({ (float)width, (float)height });
	body.setOrigin(width / 2.0f, height / 2.0f);

	position = { 0, 0 };
}

void Mouse::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		t_window.draw(body);
	}
}
