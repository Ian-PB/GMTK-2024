#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Mouse.h"
#include "Globals.h"

enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Player
{
public:

	Player();

	// "Get" functions
	sf::Vector2f getPos() { return position; }
	sf::Vector2f getCameraPos() { return camTarget; }

	// Draw all relevent features
	void draw(sf::RenderWindow& t_window);
	void update(sf::Vector2f t_mousePos);

	// Movement
	void checkDirection();

	// Attacking
	void attack(sf::Vector2f t_mousePos);
	bool attacking = false;

	bool alive = true;

	// Throwing Mouse
	Mouse mouse;
	void throwMouse(sf::Vector2f t_target);

	bool aiming = false;
	bool canAttack = true;

private:


	// Shader
	sf::Shader shadow;

	// Body
	sf::RectangleShape body;
	int width = 50;
	int height = 100;

	// Movement
	void move();

	sf::Vector2f position = { 100, 100 };;
	Direction direction;
	const int SPEED = 5;

	// Camera info needed
	sf::Vector2f camTarget;
	const int CAM_CHANGE = 100;

	// Throwing Mouse
	void aim(sf::Vector2f t_mousePos);
	sf::CircleShape crosshair;

	// Mouse info while held
	sf::Vector2f mouseHeldPos;


	// Melee
	sf::RectangleShape hitbox;
	sf::Vector2f hitboxPos;
	int hitboxWidth = 75;
	int hitboxHeight = 30;
	float hitboxRotation = 0.0f;

	bool hitboxActive = false;
	int damage = 2;
	int attackTimer = 0;
	const int ATTACK_DURATION = 20;

	// Attack cooldown info
	void attackCooldown();
	int cooldownTimer = 0;
	const int COOLDOWN_DURATION = 0.75 * 60;





	// Equations
	sf::Vector2f vectorBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return (t_b - t_a); }
	float angleBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return atan2(t_b.y - t_a.y, t_b.x - t_a.x) * (180 / PI); }
	float vectorLenght(sf::Vector2f t_a, sf::Vector2f t_b) { return (sqrt((t_b.x - t_a.x) * (t_b.x - t_a.x) + (t_b.y - t_a.y) * (t_b.y - t_a.y))); }
	sf::Vector2f scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance);
};

