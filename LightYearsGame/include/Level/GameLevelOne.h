#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly {
	class PlayerSpaceship;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* owingApp);
	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceship> mPlayerSpaceship;
		void PlayerSpaceshipDestroyed(Actor* destoryedPlayerSpaceship);

		virtual void InitGameStages() override;
		void GameOver();
	};
}