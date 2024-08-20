#include "MainMenu.h"


MainMenu::MainMenu()
{
	setupButtons();

	// Floor sprite
	if (!tilesTexture.loadFromFile("ASSETS\\IMAGES\\grass.png"))
	{
		std::cout << "problem loading sprite" << std::endl;
	}
	tilesTexture.setRepeated(true);
	tilesSprite.setTexture(tilesTexture);
	tilesSprite.setTextureRect(sf::IntRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}

void MainMenu::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	// Mouse
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event, t_window);
	}

	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
	}
}

void MainMenu::processMouseDown(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (gameplayButton.checkForMouse(mousePos))
	{
		SceneClass::currentMode = Scene::GamePlay;
	}

	if (exitGameButton.checkForMouse(mousePos))
	{
		t_window.close();
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
	t_window.draw(tilesSprite);

	t_window.draw(gameplayButton.getBody());
	t_window.draw(gameplayText);

	t_window.draw(exitGameButton.getBody());
	t_window.draw(exitText);
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

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setStyle(sf::Text::Bold);
	exitText.setCharacterSize(40U);
	exitText.setPosition({ SCREEN_WIDTH / 2.0f - 85, SCREEN_HEIGHT / 2.0f + 165 });


	gameplayButton.setup({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }, 500, 200, Scene::GamePlay, sf::Color::Blue);
	exitGameButton.setup({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 200 }, 300, 100, Scene::MainMenu, sf::Color::Red);
}
