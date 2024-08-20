#include "MainMenu.h"


MainMenu::MainMenu()
{
	setupButtons();
}

void MainMenu::processEvents(sf::Event t_event)
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

void MainMenu::processMouseDown(sf::Event t_event)
{
	if (gameplayButton.checkForMouse(mousePos))
	{
		SceneClass::currentMode = Scene::GamePlay;
	}
}

void MainMenu::processMouseMove(sf::Event t_event)
{
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}


void MainMenu::update(sf::Time t_deltaTime)
{

}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.draw(gameplayButton.getBody());
	t_window.draw(gameplayText);
}

void MainMenu::setupButtons()
{
	// Font
	if (!font.loadFromFile("ASSETS\\FONTS\\Daydream.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	// Health UI
	gameplayText.setFont(font);
	gameplayText.setString("Play");
	gameplayText.setStyle(sf::Text::Bold);
	gameplayText.setCharacterSize(50U);
	gameplayText.setPosition({ SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f - 50 });


	gameplayButton.setup({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }, 500, 200, Scene::GamePlay, sf::Color::Blue);
}
