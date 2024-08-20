// IAN PEREZ BUNUEL

/// <summary>
/// author Ian Perez Bunuel, Liam Treacy, Vit Pretchl, Sophia Stanley
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
// Scenes
#include "Globals.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Pause.h"
#include "GamePlay.h"
#include "Scenes.h"


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();


	bool m_exitGame; // control exiting game

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	// Scenes
	SplashScreen splashScreen;
	MainMenu mainMenu;
	GamePlay gameplay;
	Pause pause;

};

#endif // !GAME_HPP