#include "Level/GameLevelOne.h"
#include "gameplay/WaitStage.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"
#include "gameplay/GameStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"

namespace ly {

	GameLevelOne::GameLevelOne(Application* owingApp)
		: World{ owingApp } {

		testePlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testePlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testePlayerSpaceship.lock()->SetActorRotation(-90.f);

		//weak<Vanguard> testeSpaceship = SpawnActor<Vanguard>();
		//testeSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });

	}

	void GameLevelOne::BeginPlay()
	{
		
	}

	void GameLevelOne::InitGameStages()
	{
		AddState(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddState(shared<VanguardStage>{new VanguardStage{ this }});
		AddState(shared<WaitStage>{new WaitStage{ this, 15.f }});
		AddState(shared<TwinBladeStage>{new TwinBladeStage{ this }});
	}

}
