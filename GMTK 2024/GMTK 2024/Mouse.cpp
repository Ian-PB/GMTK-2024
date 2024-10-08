#include "Mouse.h"

Mouse::Mouse()
{
	if (!texture.loadFromFile("ASSETS/IMAGES/mouse.png"))
	{
		std::cout << "error with mouse image file";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect{ 0, 0, 16, 16 });
	sprite.setScale(4, 4);
	sprite.setOrigin(8, 8);

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
	if (active)
	{
		if (thrown)
		{
			t_window.draw(sprite/*, &thrownShader*/);
			t_window.draw(underShadow);
		}
		else
		{
			//t_window.draw(body);
			t_window.draw(sprite);
		}
	}
}

void Mouse::update(sf::Vector2f t_bearPos, int t_direction)
{
	// animate!!
	animate(t_direction);

	if (active)
	{
		// Update the position while held
		positionWhileHeld = { t_bearPos.x - (50 / 2.0f), t_bearPos.y - (100 / 4.0f) };

		// When returned
		if (returned)
		{
			// Set position to held position
			position = positionWhileHeld;
			body.setPosition(position);
			sprite.setPosition(position);
		}

		if (thrown)
		{
			throwMovement();
		}

		if (landedBool)
		{
			Landed();
		}


		// if not thrown and not on benjamin...
		else if (!thrown && !returned && !landedBool)
		{
			returnToBear();
		}
	}
}

void Mouse::returnToBear()
{
	// Variables
	float lenght = 0.0f;
	sf::Vector2f heading(0.0f, 0.0f);
	sf::Vector2f lastPos = position;

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

		// Check if moving left or right
		if (position.x > lastPos.x)
		{
			movingLeft = false;
		}
		else if (position.x < lastPos.x)
		{
			movingLeft = true;
		}
		sf::Vector2f lastPos = position;
	}
	else
	{
		returned = true;
	}

	// Set the position of the body
	body.setPosition(position);
	sprite.setPosition(position);
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
	//thrownShader.setUniform("speed", throwSpeed);

	//float throwLenght = sqrt(((positionThrownFrom.x - target.x) * (positionThrownFrom.x - target.x)) + ((positionThrownFrom.y - target.y) * (positionThrownFrom.y - target.y)));
	//thrownShader.setUniform("fullDistance", throwLenght);
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
		landedBool = true;
		framesPassedThrown = 0;
	}


	// Set the position of the body
	body.setPosition(position);
	sprite.setPosition(position);
	underShadow.setPosition(position);

	framesPassedThrown++;
	float secondsPassed = framesPassedThrown / 60.0f;
	//thrownShader.setUniform("time", secondsPassed);
}

void Mouse::Landed()
{
	if (landTimer < LAND_DURATION)
	{
		landTimer++;
	}
	else
	{
		landTimer = 0;
		landedBool = false;
	}
}

void Mouse::animate(int t_direction)
{
	ay = t_direction;
	// std::cout << ay << std::endl;

	acounter++;
	if (acounter > 3)
	{
		acounter = 0;
		ax++;
	}
	else
	{
		if (ax >= 3)
		{
			ax = 1;
		}
	}

	if (returned) // && ay <= 4)
	{
		// sprite.setTextureRect(sf::IntRect{ ((ax - 1) * 32), ((ay - 1) * 32), 32, 32 });
		sprite.setTextureRect(sf::IntRect{ 0, (ay * 32), 32, 32 });
	}
	else if (thrown) // ay == 5)
	{
		sprite.setTextureRect(sf::IntRect{ (ax * 16), 160, 16, 16 });
	}
	else if (!movingLeft && !thrown && !returned)
	{
		sprite.setTextureRect(sf::IntRect{ (ax * 16), 144, 16, 16 });
	}
	else if (movingLeft && !thrown && !returned) // ay == 7)
	{
		sprite.setTextureRect(sf::IntRect{ (ax * 16), 128, 16, 16 });
	}
	else if (!thrown && !returned)
	{
		sprite.setTextureRect(sf::IntRect{ 0, 128, 16, 16 });
	}
	else
	{
		// std::cout << "mouse image missing" << std::endl;
	}
}