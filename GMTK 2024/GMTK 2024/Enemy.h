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
	void respawn(sf::Vector2f t_playerPos);

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

	// Equations
	sf::Vector2f vectorBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return (t_b - t_a); }
	float angleBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return atan2(t_b.y - t_a.y, t_b.x - t_a.x) * (180 / PI); }
	float vectorLenght(sf::Vector2f t_a, sf::Vector2f t_b) { return (sqrt((t_b.x - t_a.x) * (t_b.x - t_a.x) + (t_b.y - t_a.y) * (t_b.y - t_a.y))); }
	sf::Vector2f calculateVectorAtDistance(sf::Vector2f origin, float angleDegrees, float distance);
	sf::Vector2f scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance);

};

