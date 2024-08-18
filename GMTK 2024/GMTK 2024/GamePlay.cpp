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
}

void GamePlay::processEvents(sf::Event t_event)
{
	// Mouse
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}

	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
	}
}

void GamePlay::processMouseDown(sf::Event t_event)
{

}

void GamePlay::processMouseMove(sf::Event t_event)
{
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}


void GamePlay::update(sf::Time t_deltaTime)
{
	// Movement of the player
	benjamin.checkDirection();

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

	// Draw Mouse (The Destroyer)
	mouse.draw(t_window);
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

	camSpeed = lenght / 5.0f;
	std::cout << camSpeed << "\n";

	heading = heading / lenght;
	heading = heading * camSpeed; // change speed to the actual speed


	// Update Pos
	camPos += heading;

	// Change the camera to be centered on the player
	camera.setCenter(camPos);
}
