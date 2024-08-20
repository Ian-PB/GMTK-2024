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
	void animate();
	int frameTimer = 0;
	const int FRAME_CHANGE = 80;

	bool checkCollision(sf::RectangleShape t_playerBody);
	void checkCollisionsOnAttacks(sf::RectangleShape t_attack, int t_damage);
	sf::Texture cloudTexture;

	int damage = 15;

	// Animation info


private:

};

