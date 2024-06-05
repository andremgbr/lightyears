#pragma once
#include "framework/World.h"

namespace ly {
	class PlayerSpaceship;
	class GameLevelOne : public World {
	public:
		GameLevelOne(Application* owingApp);
	private:
		weak<PlayerSpaceship> testePlayerSpaceship;
	};
}