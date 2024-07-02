#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly {
	class PlayerSpaceship;
	class GamePlayHUD;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* owingApp);
	private:
		virtual void AllGameStageFinished() override;
		virtual void BeginPlay() override;
		weak<PlayerSpaceship> mPlayerSpaceship;
		weak<GamePlayHUD> mGamePlayHUD;
		void PlayerSpaceshipDestroyed(Actor* destoryedPlayerSpaceship);

		virtual void InitGameStages() override;
		void QuitGame();
		void Restart();
		void GameOver();
		void SpawnCosmetics();
	};
}