#include "Level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"
#include "framework/Application.h"
#include "Level/GameLevelOne.h"

namespace ly {
	MainMenuLevel::MainMenuLevel(Application* owingApplication) 
		: World{ owingApplication }{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}
	void MainMenuLevel::BeginPlay()
	{
		mMainMenuHUD.lock()->onStartButtonCliked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		mMainMenuHUD.lock()->onQuitButtonCliked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
	}
	void MainMenuLevel::StartGame()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}
	void MainMenuLevel::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}