#include "Mouse.h"

Mouse::Mouse()
{
	// Setup body
	body.setFillColor(sf::Color::Blue);
	body.setSize({ (float)width, (float)height });
	body.setOrigin(width / 2.0f, height / 2.0f);

	// Setup the under shadow
	underShadow.setFillColor({0, 0, 0, 60});
	underShadow.setRadius(width / 2.0f);
	underShadow.setScale(2.0f, 1.0f);
	underShadow.setOrigin(width, width);

	position = { 0, 0 };

	// Throw shader setup
	if (!thrownShader.loadFromFile("ASSETS\\SHADERS\\Thrown.vert", sf::Shader::Vertex))
	{
		std::cerr << "Error loading thrown Shader" << std::endl;
	}
}


void Mouse::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		if (thrown)
		{
			t_window.draw(underShadow);
			t_window.draw(body, &thrownShader);
		}
		else
		{
			t_window.draw(body);
		}
	}
}

void Mouse::update(sf::Vector2f t_bearPos)
{
	// Update the position while held
	positionWhileHeld = { t_bearPos.x - (50 / 2.0f), t_bearPos.y - (100 / 4.0f) };

	// When returned
	if (returned)
	{
		// Set position to held position
		position = positionWhileHeld;
		body.setPosition(position);
	}

	if (thrown)
	{
		throwMovement();
	}
	// if not thrown and not on benjamin...
	else if (!thrown && !returned)
	{
		returnToBear();
	}
}

void Mouse::returnToBear()
{
	// Variables
	float lenght = 0.0f;
	sf::Vector2f heading(0.0f, 0.0f);


	// Move mouse to target
	heading.x = positionWhileHeld.x - position.x;
	heading.y = positionWhileHeld.y - position.y;
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

	// Shader info
	thrownShader.setUniform("speed", throwSpeed);

	float throwLenght = sqrt(((positionThrownFrom.x - target.x) * (positionThrownFrom.x - target.x)) + ((positionThrownFrom.y - target.y) * (positionThrownFrom.y - target.y)));
	thrownShader.setUniform("fullDistance", throwLenght);
	std::cout << throwLenght << "\n";

	std::cout << "THROW \n";
}

void Mouse::throwMovement()
{
	// Variables
	sf::Vector2f heading = { 0.0f, 0.0f };
	float lenght = 0.0f;


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
		framesPassedThrown = 0;
	}


	// Set the position of the body
	body.setPosition(position);
	underShadow.setPosition(position);

	framesPassedThrown++;
	float secondsPassed = framesPassedThrown / 60.0f;
	thrownShader.setUniform("time", secondsPassed);
}
