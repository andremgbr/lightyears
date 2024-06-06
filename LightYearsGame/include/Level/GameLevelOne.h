#pragma once
#include "framework/World.h"

namespace ly {
	class PlayerSpaceship;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* owingApp);
	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceship> testePlayerSpaceship;
		void TimerCallBack_Test();
		unsigned int timerIndex_Test;
	};
}