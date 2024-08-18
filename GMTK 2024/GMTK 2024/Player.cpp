#include "Player.h"

Player::Player()
{
	// Setup body
	body.setFillColor(sf::Color::Green);
	body.setSize({ (float)width, (float)height });
	body.setOrigin(width / 2.0f, height / 2.0f);
	body.setPosition(position);
}

void Player::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		t_window.draw(body);
	}
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