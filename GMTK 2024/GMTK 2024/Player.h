#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	sf::RectangleShape getBody() { return body; }
	sf::RectangleShape getHitbox() { return hitbox; }
	int getDamage() { return damage; }
	std::string getHealthString() { return (std::to_string(health) + " / " + std::to_string(MAX_HEALTH)); }
	int getHealth() { return health; }

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
	bool hitboxActive = false;

	void takeDamage(int t_damageAmount);
	void invulnerable();

	void animate();

	void reset();

private:


	// Shader
	sf::Shader shadow;

	// Body
	sf::RectangleShape body;
	int width = 50;
	int height = 100;

	// Sprite
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture crosshairTexture;
	sf::Texture attackTexture;
	int acounter = 0;
	int ax = 1;
	int ay = 5;

	// Audio
	sf::Sound sound;
	sf::SoundBuffer attackhit;
	sf::SoundBuffer attackmiss;
	sf::SoundBuffer step;
	sf::SoundBuffer recievedamage;
	sf::SoundBuffer jump;
	int stepCounter = 0;
	bool stepVary = true;

	// Movement
	void move();

	sf::Vector2f position = { 100, 100 };
	Direction direction;
	const int SPEED = 5;

	// Camera info needed
	sf::Vector2f camTarget;
	const int CAM_CHANGE = 100;

	// Throwing Mouse
	void aim(sf::Vector2f t_mousePos);
	sf::Sprite crosshair;

	// Mouse info while held
	sf::Vector2f mouseHeldPos;


	// Melee
	sf::RectangleShape hitbox;
	sf::Vector2f hitboxPos;
	int hitboxWidth = 100;
	int hitboxHeight = 44;
	float hitboxRotation = 0.0f;
	sf::Sprite hitboxSprite;
	
	int aFrameCount = 0;
	int attackFrame = 1;
	int damage = 20;
	int attackTimer = 0;
	const int ATTACK_DURATION = 30;

	// Attack cooldown info
	void attackCooldown();
	int cooldownTimer = 0;
	const int COOLDOWN_DURATION = 0.75 * 60;

	// Player Health
	const sf::Color INVINSABLE_COLOR = {255, 255, 255, 100};
	const sf::Color VINSABLE_COLOR = { 255, 255, 255, 255 };
	const int MAX_HEALTH = 100;
	int health = 0;
	bool invinsable = false;
	int invinsableTimer = 0;
	const int INVINSABLE_DURATION = 3 * 60;




	// Equations
	sf::Vector2f vectorBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return (t_b - t_a); }
	float angleBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return atan2(t_b.y - t_a.y, t_b.x - t_a.x) * (180 / PI); }
	float vectorLenght(sf::Vector2f t_a, sf::Vector2f t_b) { return (sqrt((t_b.x - t_a.x) * (t_b.x - t_a.x) + (t_b.y - t_a.y) * (t_b.y - t_a.y))); }

	sf::Vector2f scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance);
};

