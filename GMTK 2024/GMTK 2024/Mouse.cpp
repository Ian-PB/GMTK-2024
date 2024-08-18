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

void Mouse::update(sf::Vector2f t_bearPos)
{
	if (thrown)
	{
		throwMouse();
	}
	// if not thrown and not on benjamin...
	else if (!thrown && !returned)
	{
		returnToBear(t_bearPos);
	}
}

void Mouse::returnToBear(sf::Vector2f t_bearPos)
{
	// Variables
	float lenght = 0.0f;
	sf::Vector2f heading(0.0f, 0.0f);


	// Move mouse to target
	heading.x = t_bearPos.x - position.x;
	heading.y = t_bearPos.y - position.y;
	lenght = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	if (lenght > throwSpeed)
	{
		heading = heading / lenght;
		heading = heading * returnSpeed; // change speed to the actual speed


		// Update Pos
		position += heading;
	}
	else
	{
		returned = true;

		std::cout << "RETURNED \n";
	}


	// Set the position of the body
	body.setPosition(position);
}

void Mouse::throwMouse()
{
	thrown = true;
	returned = false;

	std::cout << "THROW \n";

	// Variables
	float lenght = 0.0f;
	sf::Vector2f heading(0.0f, 0.0f);


	// Move mouse to target
	heading.x = target.x - position.x;
	heading.y = target.y - position.y;
	lenght = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	if (lenght > throwSpeed)
	{
		heading = heading / lenght;
		heading = heading * throwSpeed; // change speed to the actual speed


		// Update Pos
		position += heading;
	}
	else
	{
		thrown = false;
	}


	// Set the position of the body
	body.setPosition(position);
}
