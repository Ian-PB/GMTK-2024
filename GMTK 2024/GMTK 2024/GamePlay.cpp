#include "GamePlay.h"


GamePlay::GamePlay()
{
	view.setSize(SCREEN_WIDTH / 1.0f, SCREEN_HEIGHT / 1.0f);

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

	// Change the camera to be centered on the player
	view.setCenter(benjamin.getPos());
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	// Setting the view of this scene
	t_window.setView(view);

	// Draw ground
	t_window.draw(tilesSprite);

	// Draw player function called
	benjamin.draw(t_window);
}