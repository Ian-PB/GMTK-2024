#include "GamePlay.h"


GamePlay::GamePlay()
{
	setupUI();

	// Camera
	camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Floor sprite
	if (!tilesTexture.loadFromFile("ASSETS\\IMAGES\\tiles.jpg"))
	{
		std::cout << "problem loading sprite" << std::endl;
	}
	tilesTexture.setRepeated(true);
	tilesSprite.setTexture(tilesTexture);
	tilesSprite.setTextureRect(sf::IntRect{ 0, 0, SCREEN_WIDTH * 10, SCREEN_HEIGHT * 10 });
	tilesSprite.setOrigin(SCREEN_WIDTH * 5, SCREEN_HEIGHT * 5);


	// Enemies
	for (int i = 0; i < 10; i++)
	{
		meleeEnemies[i].spawn();
	}
}

void GamePlay::processEvents(sf::Event t_event)
{
	// Mouse
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}
	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		processMouseUp(t_event);
	}
}

void GamePlay::processMouseDown(sf::Event t_event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (benjamin.canAttack)
		{
			benjamin.attacking = true;
		}
	}
}

void GamePlay::processMouseUp(sf::Event t_event)
{
	if (benjamin.aiming)
	{
		benjamin.throwMouse(mousePos);
	}
}

void GamePlay::processMouseMove(sf::RenderWindow& t_window)
{
	// Get the mouse position relative to the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(t_window);

	// Convert the pixel position to world coordinates
	mousePos = t_window.mapPixelToCoords(pixelPos, camera);
}

void GamePlay::setupUI()
{
	// Font
	if (!font.loadFromFile("ASSETS\\FONTS\\Daydream.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	// Health UI
	healthText.setFont(font);
	healthText.setString(benjamin.getHealthString());
	healthText.setStyle(sf::Text::Bold);
	healthText.setCharacterSize(25U);
}


void GamePlay::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{
	// Process the mouse moving even while ur not moving the mouse and just the scene
	processMouseMove(t_window);


	// Update the player
	benjamin.update(mousePos);

	// Take hit
	for (int i = 0; i < 10; i++)
	{
		if (meleeEnemies[i].alive)
		{
			if (!meleeEnemies[i].canTakeDmg)
			{
				meleeEnemies[i].invulnerable();
			}

			// Check if hit the player
			if (meleeEnemies[i].checkCollision(benjamin.getBody()))
			{
				meleeEnemies[i].knockbackTo = scaleVectorLenght(benjamin.getPos(), meleeEnemies[i].getPos(), vectorBetweenAB(benjamin.getPos(), meleeEnemies[i].getPos()), 100);
				benjamin.takeDamage(meleeEnemies[i].damage);

				healthText.setString(benjamin.getHealthString()); // Show damage taken
			}

			// Check for mouse
			meleeEnemies[i].checkForMouse(benjamin.mouse.getBody());

			// Check if should be knocked back
			if (meleeEnemies[i].knockback)
			{
				// If being knocked back then swap to this movement script
				meleeEnemies[i].knockbackMovement();
			}
			else if (meleeEnemies[i].grabbed)
			{
				meleeEnemies[i].grabLogic(benjamin.mouse.active);
			}
			else
			{
				// Move towards player
				meleeEnemies[i].move(benjamin.getPos());
			}

			if (benjamin.hitboxActive)
			{
				meleeEnemies[i].knockbackTo = scaleVectorLenght(benjamin.getPos(), meleeEnemies[i].getPos(), vectorBetweenAB(benjamin.getPos(), meleeEnemies[i].getPos()), 200);
				meleeEnemies[i].checkCollisionsOnAttacks(benjamin.getHitbox(), benjamin.getDamage());
			}
		}
	}

	updateCamera();
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	// Setting the view of this scene
	t_window.setView(camera);

	// Draw ground
	t_window.draw(tilesSprite);

	// Draw player function called
	benjamin.draw(t_window);
	t_window.draw(healthText);

	// Enemies
	for (int i = 0; i < 10; i++)
	{
		meleeEnemies[i].draw(t_window);
	}
}

void GamePlay::updateCamera()
{
	// Variables
	float lenght = 0.0f;
	sf::Vector2f heading(0.0f, 0.0f);

	sf::Vector2f target = benjamin.getCameraPos();


	heading.x = target.x - camPos.x;
	heading.y = target.y - camPos.y;
	lenght = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	camSpeed = lenght / 10.0f;

	heading = heading / lenght;
	heading = heading * camSpeed; // change speed to the actual speed


	// Update Pos
	camPos += heading;

	// Change the camera to be centered on the player
	camera.setCenter(camPos);

	// Set UI pos
	healthText.setPosition({ camPos.x - (SCREEN_WIDTH / 2.0f), camPos.y - (SCREEN_HEIGHT / 2.0f)});
}

sf::Vector2f GamePlay::scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance)
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
