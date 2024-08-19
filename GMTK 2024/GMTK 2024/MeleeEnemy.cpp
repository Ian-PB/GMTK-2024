#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
	// setup Health
	maxHealth = 100;
	// Speed
	speed = originalSpeed;

	// Dimensions
	width = 75;
	height = 40;

	hitbox.setFillColor(sf::Color::Red);
	hitbox.setSize({ (float)width, (float)height });
	hitbox.setPosition(position);
}

void MeleeEnemy::move(sf::Vector2f t_target)
{
	// Variables
	sf::Vector2f heading = { 0.0f, 0.0f };
	float lenght = 0.0f;


	// Move mouse to target
	heading.x = t_target.x - position.x;
	heading.y = t_target.y - position.y;
	lenght = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	if (lenght > speed)
	{
		heading = heading / lenght;
		heading = heading * (float)speed; // change speed to the actual speed


		// Update Pos
		position += heading;
	}


	// Set the position of the body
	hitbox.setPosition(position);
}

bool MeleeEnemy::checkCollision(sf::RectangleShape t_playerBody)
{
	if (t_playerBody.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
	{
		knockback = true;
		speed = knockbackSpeed;

		return true;
	}

	return false;
}

void MeleeEnemy::knockbackMovement()
{
	// Variables
	sf::Vector2f heading = { 0.0f, 0.0f };
	float length = 0.0f;

	// Move mouse to target
	heading.x = knockbackTo.x - position.x;
	heading.y = knockbackTo.y - position.y;
	length = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	if (length > speed)
	{
		// Normalize the heading vector
		heading = heading / length;

		// Apply a smooth deceleration as the object approaches the target
		float smoothingFactor = std::min(length / 100.0f, 1.0f); // Adjust 100.0f to control the smoothing effect
		float adjustedSpeed = speed * smoothingFactor;

		// Calculate the final heading based on the adjusted speed
		heading = heading * adjustedSpeed;

		// Update the position
		position += heading;
	}
	else
	{
		// Reset the speed and stop knockback when the target is reached
		speed = originalSpeed;
		knockback = false;
	}

	// Set the position of the body
	hitbox.setPosition(position);

}
