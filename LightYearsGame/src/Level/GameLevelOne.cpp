#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"

namespace ly {

	GameLevelOne::GameLevelOne(Application* owingApp)
		: World{ owingApp } {

		testePlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testePlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testePlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testeSpaceship = SpawnActor<Vanguard>();
		testeSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });

	}

	void GameLevelOne::BeginPlay()
	{
		timerIndex_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallBack_Test, 3, true);
	}

	void GameLevelOne::TimerCallBack_Test()
	{
		LOG("CallBack callded!!");
		TimerManager::Get().ClearTimer(timerIndex_Test);
	}

}
