#include "Player.h"

Player::Player()
{
	// Setup body
	body.setFillColor(sf::Color::Green);
	body.setSize({ (float)width, (float)height });
	body.setOrigin(width / 2.0f, height / 2.0f);
	body.setPosition(position);

	crosshair.setFillColor(sf::Color::Red);
	crosshair.setRadius( 20 );
	crosshair.setOrigin( 20, 20);


	// Setup Shadow Shader
	if (!shadow.loadFromFile("ASSETS\\SHADERS\\Shadow.vert", "ASSETS\\SHADERS\\Shadow.frag"))
	{
		std::cerr << "Error loading shadow Shader" << std::endl;
	}
	// Set texture uniform in shader
	shadow.setUniform("u_texture", sf::Shader::CurrentTexture);
}

void Player::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		t_window.draw(body, &shadow);
		t_window.draw(body);

		if (aiming)
		{
			t_window.draw(crosshair);
		}
	}


	// Mouse Draw
	mouse.draw(t_window);
}

void Player::update(sf::Vector2f t_mousePos)
{
	// Movement
	checkDirection();

	// Throwing
	// Check if the right mouse button is held down
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
	{
		aim(t_mousePos);
	}
	else
	{
		aiming = false;
	}


	// Mouse Updates
	mouse.update(position);
}

void Player::move()
{
	sf::Vector2f movement = { 0.0f, 0.0f };

	switch (direction)
	{
	case Direction::None:
		break;

	case Direction::Up:
		movement.y = -SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.y = (position.y + movement.y) - CAM_CHANGE;

		break;

	case Direction::Down:
		movement.y = SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.y = (position.y + movement.y) + CAM_CHANGE;

		break;

	case Direction::Left:
		movement.x = -SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.x = (position.x + movement.x) - CAM_CHANGE;

		break;

	case Direction::Right:
		movement.x = SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.x = (position.x + movement.x) + CAM_CHANGE;

		break;
	}


	position += movement;
	body.setPosition(position); // change hitbox position
}



void Player::aim(sf::Vector2f t_mousePos)
{
	aiming = true;

	crosshair.setPosition(t_mousePos);
}


void Player::checkDirection()
{
	direction = Direction::None;

	// Camera change
	if (direction == Direction::None)
	{
		camTarget = position;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = Direction::Up;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = Direction::Down;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = Direction::Left;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = Direction::Right;
		move();
	}
}

void Player::throwMouse(sf::Vector2f t_target)
{
	// Acitvate mouse thrown
	mouse.throwSelf(position, t_target);
}
