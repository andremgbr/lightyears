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
#include "Enemy/HexagonStage.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "player/PlayerManager.h"
#include "widgets/GamePlayHUD.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"

namespace ly {

	GameLevelOne::GameLevelOne(Application* owingApp)
		: World{ owingApp } {
		

	}

	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGamePlayHUD = SpawnHUD<GamePlayHUD>();
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destoryedPlayerSpaceship)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!mPlayerSpaceship.expired()) {
			mPlayerSpaceship.lock()->onActorDestoryed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else {

			GameOver();
		}
	}

	void GameLevelOne::InitGameStages()
	{

		AddState(shared<BossStage>{new BossStage{ this }});

		AddState(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddState(shared<VanguardStage>{new VanguardStage{ this }});

		AddState(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddState(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddState(shared<WaitStage>{new WaitStage{ this, 15.f }});
		AddState(shared<HexagonStage>{new HexagonStage{ this }});

		AddState(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddState(shared<UFOStage>{new UFOStage{ this }});

		AddState(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddState(shared<ChaosStage>{new ChaosStage{ this }});
	}

	void GameLevelOne::GameOver()
	{
		LOG("Game is OVER<<<<<<<<<<<<<<<<<<<<<<<<<");
	}

}
