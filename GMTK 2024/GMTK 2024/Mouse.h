#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>




class Mouse
{
public:
	Mouse();

	// "Get" functions
	sf::Vector2f getPos() { return position; }
	sf::RectangleShape getBody() { return body; }

	// Draw all relevent features
	void draw(sf::RenderWindow& t_window);
	void update(sf::Vector2f t_bearPos, int t_direction);
	void returnToBear();
	void animate(int t_direction);

	// Throwing
	void throwSelf(sf::Vector2f t_initialPos, sf::Vector2f t_target);
	void throwMovement();
	sf::Vector2f target;
	bool thrown = false;
	bool returned = false;

	void Landed();
	int landTimer = 0;
	const int LAND_DURATION = 0.5 * 60;
	bool canAttack = false;
	bool movingLeft = true;

	int acounter = 0;
	int ax = 1;
	int ay = 0;
	int raisecounter = 0;

	bool active = true;


private:

	// Body
	sf::RectangleShape body;
	sf::Sprite sprite;
	sf::Texture texture;
	float scale = 1.0f;
	int width = 20;
	int height = 20;

	sf::Vector2f position;
	sf::Vector2f positionWhileHeld;

	// Throwing
	sf::CircleShape underShadow;
	sf::Shader thrownShader;
	sf::Vector2f positionThrownFrom;
	float throwSpeed = 12.5f;
	// Time keeping for shader
	int framesPassedThrown = 0;

	// Returning
	float returnSpeed = 6.5f;

};

