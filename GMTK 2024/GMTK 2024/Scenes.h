// IAN PEREZ BUNUEL

#pragma once

enum class Scene
{
	None,
	SplashScreen,
	MainMenu,
	Pause,
	GamePlay
};

class SceneClass
{
public:
	SceneClass() { currentMode = Scene::None; }
	static Scene currentMode;
};