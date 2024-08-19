#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Player.h"

class Enemy
{
public:
	Enemy();

	// "Get" functions
	sf::Vector2f getPos() { return position; }

	void draw(sf::RenderWindow &t_window);

	void spawn();

	virtual bool checkCollision(sf::RectangleShape t_playerBody);

	void takeDamage(int t_damage);
	void knockbackMovement();
	bool knockback = false;
	sf::Vector2f knockbackTo;

	bool alive = false;

	void invulnerable();
	bool canTakeDmg = true;

protected:

	// Sprite
	sf::Sprite sprite;
	sf::Texture texture;

	// Hitbox
	sf::RectangleShape hitbox;
	int width = 0;
	int height = 0;

	sf::Vector2f position = { 0.0f, 0.0f };
	int speed = 0;
	int originalSpeed = 0;
	int knockbackSpeed = 0;

	// Health
	int maxHealth;
	int health = maxHealth;
	int invinsableTimer = 0;
	const int INVINSABLE_DURATION = 0.5 * 60;

private:

};

