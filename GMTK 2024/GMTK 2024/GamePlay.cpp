#include "GamePlay.h"


GamePlay::GamePlay()
{
	camera.setSize(SCREEN_WIDTH / 1.0f, SCREEN_HEIGHT / 1.0f);

	if (!tilesTexture.loadFromFile("ASSETS\\IMAGES\\tiles.jpg"))
	{
		std::cout << "problem loading sprite" << std::endl;
	}
	tilesTexture.setRepeated(true);
	tilesSprite.setTexture(tilesTexture);
	tilesSprite.setTextureRect(sf::IntRect{ 0, 0, SCREEN_WIDTH * 10, SCREEN_HEIGHT * 10 });
	tilesSprite.setOrigin(SCREEN_WIDTH * 5, SCREEN_HEIGHT * 5);
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


void GamePlay::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{
	// Process the mouse moving even while ur not moving the mouse and just the scene
	processMouseMove(t_window);


	// Update the player
	benjamin.update(mousePos);

	// Take hit
	// for (int i = 0; i < enemyAmount; i++)
	// {
	//		if (enemies[i].checkCollision())
	//		{
	//			benjamin.takeDamage(enemies[i].damage);
	//		}
	// }

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
}
