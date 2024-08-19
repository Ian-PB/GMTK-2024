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
}

bool Enemy::checkCollision(sf::RectangleShape t_playerBody)
{
	if (t_playerBody.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
	{
		return true;
	}

	return false;
}