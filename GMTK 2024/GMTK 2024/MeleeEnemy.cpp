#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
	// Sprite
	if (!texture.loadFromFile("ASSETS/IMAGES/golem.png"))
	{
		std::cout << "error with enemy image file";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect{ 0, 32, 16, 16 });

	sprite.setOrigin(8, 8);
	sprite.setScale(4, 4);


	// setup Health
	maxHealth = 100;
	// Speed
	originalSpeed = 4;
	knockbackSpeed = originalSpeed * 2;
	speed = originalSpeed;

	// Dimensions
	width = 50;
	height = 50;

	hitbox.setFillColor(sf::Color::Red);
	hitbox.setSize({ (float)width, (float)height });
	hitbox.setOrigin(width / 2.0, height / 2.0);
	hitbox.setPosition(position);

	sprite.setPosition(position);

	
}

void MeleeEnemy::move(sf::Vector2f t_target)
{
	// Variables
	sf::Vector2f heading = { 0.0f, 0.0f };
	float lenght = 0.0f;

	sf::Vector2f lastPos = position;


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


		// Check if moving left or right
		if (position.x > lastPos.x)
		{
			movingLeft = false;
		}
		else if (position.x < lastPos.x)
		{
			movingLeft = true;
		}
	}


	// Set the position of the body
	hitbox.setPosition(position);
	sprite.setPosition(position);
}

void MeleeEnemy::animate()
{
	for (int i = 0; i < 8; i++)
	{
		if (frameTimer < FRAME_CHANGE)
		{
			frameTimer++;
		}
		else
		{
			if (movingLeft)
			{
				sprite.setTextureRect(sf::IntRect{ 16 * i, 32, 16, 16 });
			}
			else
			{
				sprite.setTextureRect(sf::IntRect{ 16 * i, 48, 16, 16 });
			}

			frameTimer = 0;
		}
	}
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
