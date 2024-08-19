#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
	// setup Health
	maxHealth = 100;
	// Speed
	originalSpeed = 4;
	knockbackSpeed = originalSpeed * 2;
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
		takeDamage(0);

		return true;
	}

	return false;
}

void MeleeEnemy::checkCollisionsOnAttacks(sf::RectangleShape t_attack, int t_damage)
{
	if (t_attack.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
	{
		takeDamage(t_damage);
	}
}
