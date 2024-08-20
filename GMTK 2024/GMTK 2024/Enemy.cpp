#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		// t_window.draw(hitbox);
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

void Enemy::respawn(sf::Vector2f t_playerPos)
{
	sf::Vector2f newPos;

	// Make new spawnPoint
	float randAngleD = rand() % 180;
	if (rand() % 2 == 0)
	{
		randAngleD *= -1;
	}

	newPos = calculateVectorAtDistance(t_playerPos, randAngleD, SCREEN_HEIGHT);


	// Reset position
	position = newPos;
	hitbox.setPosition(position);
	sprite.setPosition(position);

	// Reset Health
	health = maxHealth;
	alive = true;
}

void Enemy::respawnTimer(sf::Vector2f t_playerPos)
{
	if (deathTimer < DEATH_DURATION)
	{
		deathTimer++;
	}
	else
	{
		deathTimer = 0;
		respawn(t_playerPos);
	}
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
	}
}

void Enemy::takeDamage(int t_damage, bool t_knockback)
{
	if (canTakeDmg && t_damage > 0)
	{
		health -= t_damage;

		if (health <= 0)
		{
			alive = false;
			grabbed = false;
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
	sprite.setPosition(position);
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

sf::Vector2f Enemy::calculateVectorAtDistance(sf::Vector2f origin, float angleDegrees, float distance)
{
	// Convert the angle from degrees to radians (trigonometric functions in C++ use radians)
	float angleRadians = angleDegrees * (3.14159265f / 180.0f);

	// Calculate the X and Y offsets using trigonometry
	float offsetX = distance * cos(angleRadians);
	float offsetY = distance * sin(angleRadians);

	// Create the new vector at the specified distance and angle
	sf::Vector2f result = origin + sf::Vector2f(offsetX, offsetY);

	return result;
}

sf::Vector2f Enemy::scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance)
{
	float angle = atan2f(t_vecBetweenPoints.y, t_vecBetweenPoints.x);

	// Calculate the total length of the line
	float totalLength = vectorLenght(t_startPoint, t_endPoint);

	// Calculate the ratio of the desired length to the total length of the line
	float ratio = t_distance / totalLength;

	// Calculate the coordinates of the point at the desired length along the line
	float newX = t_startPoint.x + ratio * (t_endPoint.x - t_startPoint.x);
	float newY = t_startPoint.y + ratio * (t_endPoint.y - t_startPoint.y);

	return { newX, newY };
}

void Enemy::checkForMouse(sf::RectangleShape t_mouseBody)
{
	if (t_mouseBody.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
	{
		grabbed = true;
	}
}

void Enemy::grabLogic(bool &t_mouseActive)
{
	t_mouseActive = false;

	if (grabTimer < 5)
	{
		grabTimer++;
	}
	else
	{
		takeDamage(2, false);
	}

	if (!alive)
	{
		t_mouseActive = true;
	}

	// Swap texture
	
}
