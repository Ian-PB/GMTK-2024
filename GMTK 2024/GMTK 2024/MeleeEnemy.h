#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Enemy.h"

class MeleeEnemy : public Enemy
{
public:
	MeleeEnemy();

	void move(sf::Vector2f t_target);

	bool checkCollision(sf::RectangleShape t_playerBody);

	void knockbackMovement();
	bool knockback = false;


	int damage = 15;

	sf::Vector2f knockbackTo;

private:

	int originalSpeed = 4;
	int knockbackSpeed = originalSpeed * 2;

};

