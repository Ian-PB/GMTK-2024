#include "Player.h"

Player::Player()
{
	// Setup body
	body.setFillColor(sf::Color::Green);
	body.setSize({ (float)width, (float)height });
	if (!texture.loadFromFile("ASSETS/IMAGES/bear.png"))
	{
		std::cout << "error with player image file";
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect{ 0, 128, 32, 32});
	sprite.setScale(4, 4);
	sprite.setOrigin(16, 16);
	sprite.setPosition(position);

	body.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
	body.setOrigin(width / 2.0f, height / 2.0f);
	body.setPosition(position);

	hitbox.setFillColor(sf::Color::Red);
	hitbox.setSize({ (float)hitboxWidth, (float)hitboxHeight });
	hitbox.setOrigin(hitboxWidth / 2.0f, hitboxHeight / 2.0f);

	crosshair.setFillColor(sf::Color::Red);
	crosshair.setRadius( 20 );
	crosshair.setOrigin( 20, 20);


	// Setup Shadow Shader
	if (!shadow.loadFromFile("ASSETS\\SHADERS\\Shadow.vert", "ASSETS\\SHADERS\\Shadow.frag"))
	{
		std::cerr << "Error loading shadow Shader" << std::endl;
	}
	// Set texture uniform in shader
	shadow.setUniform("u_texture", sf::Shader::CurrentTexture);

	// Setup mouse held position
	mouseHeldPos = {position.x + (width / 2.0f), position.y + ((height / 4.0f) * 3) };


	// Setup Health
	health = MAX_HEALTH;

}

void Player::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		t_window.draw(sprite, &shadow);
		t_window.draw(sprite);
		// t_window.draw(body);

		if (aiming)
		{
			t_window.draw(crosshair);
		}
	}

	if (hitboxActive)
	{
		t_window.draw(hitbox);
	}


	// Mouse Draw
	mouse.draw(t_window);
}

void Player::update(sf::Vector2f t_mousePos)
{
	// Movement
	checkDirection();

	// Animation
	animate();

	// Throwing
	// Check if the right mouse button is held down
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
	{
		if (mouse.returned)
		{
			aim(t_mousePos);
		}
	}
	else
	{
		aiming = false;
	}

	if (attacking)
	{
		attack(t_mousePos);
	}

	if (!canAttack)
	{
		attackCooldown();
	}

	// Invinsablility timer
	if (invinsable)
	{
		invulnerable();
	}

	// Mouse Updates
	mouse.update(position);
}

void Player::move()
{
	sf::Vector2f movement = { 0.0f, 0.0f };

	switch (direction)
	{
	case Direction::None:
		break;

	case Direction::Up:
		movement.y = -SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.y = (position.y + movement.y) - CAM_CHANGE;

		break;

	case Direction::Down:
		movement.y = SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.y = (position.y + movement.y) + CAM_CHANGE;

		break;

	case Direction::Left:
		movement.x = -SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.x = (position.x + movement.x) - CAM_CHANGE;

		break;

	case Direction::Right:
		movement.x = SPEED;

		// Make sure the camera is slightly ahead of the player
		camTarget.x = (position.x + movement.x) + CAM_CHANGE;

		break;
	}


	position += movement;
	sprite.setPosition(position); // change hitbox position
	body.setPosition(position); // change hitbox position
	mouseHeldPos = { position.x + (width / 2.0f), position.y + ((height / 4.0f) * 3) }; // Update mouse held pos
}



void Player::aim(sf::Vector2f t_mousePos)
{
	aiming = true;

	crosshair.setPosition(t_mousePos);
}


void Player::checkDirection()
{
	direction = Direction::None;

	// Camera change
	if (direction == Direction::None)
	{
		camTarget = position;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = Direction::Up;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = Direction::Down;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = Direction::Left;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = Direction::Right;
		move();
	}
}

void Player::attack(sf::Vector2f t_mousePos)
{
	hitboxActive = true;
	canAttack = false;

	if (attackTimer < ATTACK_DURATION)
	{
		attackTimer++;

		if (attackTimer == 1)
		{
			sf::Vector2f attackPos = vectorBetweenAB(position, t_mousePos);

			attackPos = scaleVectorLenght(position, t_mousePos, attackPos, 75);

			hitboxPos = attackPos;
			hitboxRotation = angleBetweenAB(position, t_mousePos);


			hitbox.setRotation(hitboxRotation + 90);
			hitbox.setPosition(attackPos);
		}
	}
	else
	{
		attackTimer = 0;
		hitboxActive = false;
		attacking = false;
	}
}

void Player::throwMouse(sf::Vector2f t_target)
{
	// Acitvate mouse thrown
	mouse.throwSelf(position, t_target);
}

void Player::takeDamage(int t_damageAmount)
{
	if (!invinsable)
	{
		health -= t_damageAmount;
		sprite.setColor(INVINSABLE_COLOR);
	}

	invinsable = true;
}

void Player::invulnerable()
{
	if (invinsableTimer < INVINSABLE_DURATION)
	{
		invinsableTimer++;
	}
	else
	{
		invinsableTimer = 0;
		invinsable = false;

		sprite.setColor(VINSABLE_COLOR);
	}
}

void Player::attackCooldown()
{
	if (cooldownTimer < COOLDOWN_DURATION + ATTACK_DURATION)
	{
		cooldownTimer++;
	}
	else
	{
		cooldownTimer = 0;
		canAttack = true;
	}
}

sf::Vector2f Player::scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance)
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

void Player::animate()
{
	// std::cout << "I AM ANIMATING!!!!!" << std::endl;

	acounter++;
	if (acounter > 5)
	{
		acounter = 0;
		ax++;
	}
	else
	{
		if (ax >= 8)
		{
			ax = 1;
		}
	}

	switch (direction)
	{
	case Direction::None:
		ay = 0;
		break;
	case Direction::Down:
		ay = 1;
		break;
	case Direction::Up:
		ay = 2;
		break;
	case Direction::Left:
		ay = 3;
		break;
	case Direction::Right:
		ay = 4;
		break;
	}

	if (ay > 0)
	{
		sprite.setTextureRect(sf::IntRect{ ((ax - 1) * 32), ((ay - 1) * 32), 32, 32 });
	}
	else
	{
		sprite.setTextureRect(sf::IntRect{ 0, 128, 32, 32 });
	}


}