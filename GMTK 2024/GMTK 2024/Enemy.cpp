#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		t_window.draw(hitbox);
		t_window.draw(sprite);
	}
}



void Enemy::spawn()
{
	alive = true;

	position = { 100, 100 };
	hitbox.setPosition(position);
	sprite.setPosition(position);

	health = maxHealth;
}

bool Enemy::checkCollision(sf::RectangleShape t_playerBody)
{
	if (t_playerBody.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void Enemy::takeDamage(int t_damage)
{
	knockback = true;
	speed = knockbackSpeed;

	if (canTakeDmg && t_damage > 0)
	{
		health -= t_damage;

		canTakeDmg = false;

		if (health <= 0)
		{
			alive = false;
		}

		std::cout << health << "\n";
	}
}

void Enemy::knockbackMovement()
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

void Enemy::invulnerable()
{
	if (invinsableTimer < INVINSABLE_DURATION)
	{
		invinsableTimer++;
	}
	else
	{
		invinsableTimer = 0;
		canTakeDmg = true;
	}
}
