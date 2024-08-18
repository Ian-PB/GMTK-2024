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
		throwMovement();
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

void Mouse::throwSelf(sf::Vector2f t_initialPos, sf::Vector2f t_target)
{
	thrown = true;
	returned = false;

	// Get the initial position
	positionThrownFrom = t_initialPos;
	// Set the target position
	target = t_target;

	std::cout << "THROW \n";
}

void Mouse::throwMovement()
{
	// Variables
	sf::Vector2f heading = { 0.0f, 0.0f };
	float progress = 0.0f;


	// Move mouse to target
	heading.x = target.x - position.x;
	heading.y = target.y - position.y;
	float length = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	if (length > throwSpeed)
	{
		heading = heading / length;
		heading = heading * throwSpeed; // change speed to the actual speed

		// Calculate the arc using a sine function
		float progress = (target.x - position.x) / (target.x - positionThrownFrom.x);
		heading.y += sinf(progress * 3.14f) * arcHeight; // Adjust arcHeight to control how high the arc goes

		// Update Position
		position += heading;


		// Scale the body based on progress
		scale = 1.0f + (progress * 2.3f) * sinf(progress * 3.14f); // Scale from 1.0 to 5.0 and back to 1.0
		body.setScale(scale, scale);

		// Set the position of the body
		body.setPosition(position);
	}
	else
	{
		thrown = false;

		scale = 1.0f;
		body.setScale(scale, scale);
	}
}
